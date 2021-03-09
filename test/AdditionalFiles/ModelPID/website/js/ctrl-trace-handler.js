moduleSWV.controller("ctrl-trace-handler", function ($scope, $log, $http, $interval) {
    $log.log("[ctrl-trace-handler]: wurde initialisiert");

    $scope.Trace_Config = null;
    $scope.TPS_Config = 0;
    $scope.plot = null;

    const updateInterval = 100;
    $scope.measureInterval = 10;
    // $scope.totalPoints = 100;
    // $scope.updateInterval = 100;
    $scope.dataset = null;
    $scope.IntervalProcess = null;
    $scope.startTime = null;
    $scope.maxY = 100;
    $scope.minY = 0;
    $scope.traceActive = false;

    $scope.$watch("minY", renderTrace);
    $scope.$watch("maxY", renderTrace);
    $scope.$watch("measureInterval", renderTrace);

    $scope.$watch("CurrentTrace", function (newValue, oldValue) {
        if (newValue !== "" && !$scope.traceActive) {
            $scope.startTrace();
        }
    });

    $log.log("[ctrl-trace-handler]: lade TPS config");
    //todo bugfix for Model testing
    $http.get("param/Model_TestPointedSignals.json").then(function (response) {
        $scope.TPS_Config = response.data;
    });

    $scope.toggleTrace = function () {
        if ($scope.traceActive) {
            $scope.stopTrace();
        } else {
            $scope.startTrace();
        }
    };

    $scope.toggleBtnTxt = function () {
        if ($scope.traceActive)
            return "Stop";
        else
            return "Start";
    };

    $scope.startTrace = function () {
        $log.log("[ctrl-trace-handler]: start trace");
        $http.get("param/" + $scope.CurrentTrace + ".json").then(function (response) {
            $scope.Trace_Config = response.data;
        });

        $scope.dataset = null;
        $scope.data_Trace = [];
        $scope.startTime = $scope.TPS_Values.Time;
        $scope.IntervalProcess = $interval(function () {
            if ($scope.Trace_Config !== null) {
                //$log.log($scope.ReadData());
                $scope.PlotRealtimeScope($scope.Trace_Config);
            }
        }, updateInterval);

        $scope.traceActive = true;
    };

    $scope.closeTrace = function () {
        if ($scope.plot === null) {
            $log.log("[ctrl-trace-handler]: close trace");
            $scope.$emit("close-Trace");
        }
        else {
            $scope.stopTrace(true);
            $log.log("[ctrl-trace-handler]: close trace");
            $scope.plot.destroy();
            $scope.plot = null;
            $scope.dataset = null;
            $scope.Trace_Config = null;
            $scope.$emit("close-Trace");
        }
    };

    /**
     *
     * @param suppressRender Don't render trace. This is used to prevent exceptions during shutdown
     */
    $scope.stopTrace = function (suppressRender) {
        $log.log("[ctrl-trace-handler]: stop trace");
        // $scope.dataset.forEach(function (currentDataset) {
        //     currentDataset.data = [];
        // });
        $interval.cancel($scope.IntervalProcess);

        $scope.traceActive = false;
        if (!suppressRender) {
            renderTrace();
        }
    };

    /**
     * Stores a flot graph to a png file with the specified filename
     */
    $scope.traceToPNG = function () {
        const filename = "Webvisu_Trace_" + new Date().toString();
        const plotCanvas = $scope.plot.getCanvas();
        const imageURL = plotCanvas.toDataURL();
        //Create a new link element and trigger a click event. Remove it afterwards
        const link = $("<a href='" + imageURL + "' download='" + filename + "'></a>");
        link[0].click();
        link.remove();
    };

    $scope.autoScale = function () {
        if ($scope.plot !== null) {
            $scope.minY = null;
            $scope.maxY = null;
        }
    };

    $scope.PlotRealtimeScope = function (TraceConfig) {
        // $log.log($scope.TPS_Values.Time);

        $scope.ReadData(TraceConfig);

        renderTrace();

        const yaxis = $scope.plot.getAxes().yaxis;
        $scope.minY = yaxis.min;
        $scope.maxY = yaxis.max;
        //$scope.plot.setData([$scope.ReadData(TraceConfig)]);
        //$scope.plot.draw();
    };

    function renderTrace() {
        if ($scope.dataset === null)
            return;

        $scope.plot = $.plot("#placeholder", $scope.dataset, {
            canvas: true,
            series: {
                lines: {
                    show: true
                },
                shadowSize: 1	// Drawing is faster without shadows
            },
            // colors: [ "#3058E9", "#4D8958", "#000000"],
            legend: {
                backgroundColor: "#444444"
            },
            yaxis: {
                color: "#ffffff",
                min: $scope.minY,
                max: $scope.maxY
            },
            xaxis: {
                color: "#ffffff",
                tickcolor: "#ffffff",
                min: 0,
                max: $scope.measureInterval * (1000 / updateInterval),
                alignTicksWithAxis: 200,
                tickFormatter: function (val) {
                    return (val / 10) + "s";
                }
            },
            grid: {
                color: "#ffffff",
                backgroundColor: "#000000"
            },
            zoom: {
                interactive: !$scope.traceActive
            },
            pan: {
                interactive: !$scope.traceActive
            }
        });
    }

    $scope.ReadData = function (TraceConfig) {
        //setup dataset
        if ($scope.dataset === null) {
            $scope.dataset = [];
            TraceConfig.TraceConfig.Inputs.forEach(function (currentInput) {
                let tmpDataset =
                    {
                        label: currentInput,
                        data: []
                    };
                $scope.dataset.push(tmpDataset);
            });
        }

        //check timestamp, clear data set and save the new start time
        $scope.dataset.forEach(function (currentDataSet) {
            //check data exists
            if (currentDataSet.data.length > 0) {
                //check timestamp from last entry
                if (currentDataSet.data[currentDataSet.data.length - 1][0] > ($scope.measureInterval * (1000 / updateInterval))) {
                    //clear dataset
                    currentDataSet.data = [];
                    $scope.startTime = $scope.TPS_Values.Time;
                }
            }
        });


        //add new value
        $scope.dataset.forEach(function (currentDataset) {
            //search the value id from currentDataset TPS
            let idOfTps;
            $scope.TPS_Config.TestPointedSignals.forEach(function (currentTPS, indexTPS) {
                if (currentTPS.Name === currentDataset.label) {
                    idOfTps = indexTPS;
                }
            });

            //create timestamp resolution 0.1s or 100ms
            let timestamp = Math.round(($scope.TPS_Values.Time - $scope.startTime) / 100);
            if (timestamp < 0) {                              //stop of plc
                currentDataset.data = [];                      //clear dataset
                $scope.startTime = $scope.TPS_Values.Time   //set new startTime
            }

            //add new value
            currentDataset.data.push([timestamp, $scope.TPS_Values.TestPointedSignals[idOfTps]]);
        });

        //exit
        return $scope.dataset;
    }
});

