/*      controller for basic operations of simulink web visu
 *
 *      This controller provide some basic operations of the simulink web visualization.
 *      Additionally to the operations provide this controller the main application struct
 *      of the single-page-application.
 */

moduleSWV.controller("ctrl-basic-operations", function ($scope, $log, $http, $sce, $interval) {
    $log.log("[ctrl-basic-operations]: wurde initialisiert");

    $scope.TPS_Values = 0;

    //Settings
    $scope.ModelName = "";
    $scope.UserTitle = "";
    $scope.ShowMenueP = false;
    $scope.ShowMenueWSP = false;
    $scope.ShowMenueMWSP = false;
    $scope.ShowParams = false;
    $scope.ShowTrace = false;
    $scope.ShowBackSvgFunction = false;
    $scope.Configuration = "";
    $scope.CurrentSvgModel = "";
    $scope.PreSvgModels = [];
    $scope.CurrentTrace = "";
    $scope.SubSystemName = "";
    $scope.WriteEnabled = false;

    $http.get("param/config.json").then(function (response) {
        $scope.Configuration = response.data;
        $scope.ModelName = $scope.Configuration.ModelName;
        $scope.ShowMenueP = $scope.Configuration.Parameter;
        $scope.ShowMenueWSP = $scope.Configuration.WorkspaceParameter;
        $scope.ShowMenueMWSP = $scope.Configuration.ModelWorkspaceParameter;
        $scope.UserTitle = $scope.Configuration.Title;
        $scope.SubSystemName = $scope.Configuration.Title;
    });

    $http.get("param/Model.json").then(function (response) {
        $scope.CurrentSvgModel = $scope.replacer(response.data);
        $scope.RootSvgModel = $scope.CurrentSvgModel;
        $scope.UserTitle = $scope.CurrentSvgModel.FullBlockPath.replace('./svg/', '').replace('.svg', '');
        $scope.SubSystemName = $scope.CurrentSvgModel.Name;
        $scope.$broadcast("open-SVG", $scope.CurrentSvgModel.FullBlockPath);
    });


    //Function - Area
    $scope.trustedHtml = function (plainText) {
        return $sce.trustAsHtml(plainText);
    };

    $scope.openPreviousSvg = function () {
        $scope.$broadcast("open-SVG", $scope.PreSvgModels[$scope.PreSvgModels.length - 1].FullBlockPath);
        $scope.CurrentSvgModel = $scope.PreSvgModels[$scope.PreSvgModels.length - 1];
        $scope.PreSvgModels.pop();

        $scope.UserTitle = $scope.CurrentSvgModel.FullBlockPath.replace('./svg/', '').replace('.svg', '');
        $scope.SubSystemName = $scope.CurrentSvgModel.Name;

        if ($scope.PreSvgModels.length === 0) {
            $scope.ShowBackSvgFunction = false;
        }
    };

    $scope.openSvg = function (targetModel) {
        if ($scope.CurrentSvgModel !== targetModel) {
            $log.log("[ctrl-basic-operations]: call svg model:" + targetModel.FullBlockPath);
            $scope.$broadcast("open-SVG", targetModel.FullBlockPath);
            $scope.ShowBackSvgFunction = true;
            $scope.PreSvgModels[$scope.PreSvgModels.length] = $scope.CurrentSvgModel;
            $scope.CurrentSvgModel = targetModel;
            $scope.Configuration.Title = targetModel.Name;
            $scope.UserTitle = targetModel.FullBlockPath.replace('./svg/', '').replace('.svg', '');
            $scope.SubSystemName = targetModel.Name;
        }
    };

    $scope.openParams = function (typ, access, enableFilter) {
        $log.log("[ctrl-basic-operations]: show param settings");
        $scope.ShowParams = true;
        $scope.$broadcast("open-params", typ, access, enableFilter);

        // Listen for clicks outside of the params menu
        setTimeout(() => $(document).bind("click", handleParamWindowClick), 100);
    };

    function handleParamWindowClick(e) {
        const paramWindow = $("#ParameterSetting").find(".Container");
        if (!paramWindow.is(e.target) && paramWindow.has(e.target).length === 0) {
            $scope.$emit("close-Params");
        }
    }

    function handleTraceWindowClick(e) {
        const paramWindow = $("#SimulinkScope").find(".Container");
        if (!paramWindow.is(e.target) && paramWindow.has(e.target).length === 0) {
            $scope.$emit("close-Trace");
        }
    }

    //Data Exchange between cpu and browser
    $scope.readTPS = function () {
        $http.get("param/TestPointedSignals.json").then(function (response) {
            let modelscope = angular.element($("#SVG_Graphic")).scope();
            $scope.TPS_Values = $scope.replacer(response.data);
            modelscope.editTPS();

            //Update write enable status
            $scope.WriteEnabled = $scope.TPS_Values.WriteEnabled;
        });
    };
    $interval(function () {
        $scope.readTPS();
    }, 200);

    $scope.$on("close-Params", function (event) {
        $(document).unbind("click", handleParamWindowClick);
        $scope.ShowParams = false;
    });

    $scope.$on("close-Trace", function (event) {
        $(document).unbind("click", handleTraceWindowClick);
        $scope.ShowTrace = false;
    });

    $scope.openTrace = function (name_of_config) {
        $scope.ShowTrace = true;
        $scope.CurrentTrace = name_of_config;

        // Listen for clicks outside of the trace
        setTimeout(() => $(document).bind("click", handleTraceWindowClick), 100);
    };

    $scope.replacer = function (input) {
        let test = JSON.stringify(input);
        test = test.replace(new RegExp("(\&#x2d;)", 'g'), "-");
        return JSON.parse(test);
    };

    $scope.formatWriteEnabled = function () {
        if ($scope.WriteEnabled == true) {
            return "Enabled";
        } else {
            return "Disabled";
        }
    };
});