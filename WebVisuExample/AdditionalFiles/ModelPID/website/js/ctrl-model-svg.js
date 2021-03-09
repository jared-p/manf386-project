moduleSWV.controller("ctrl-model-svg", function ($scope, $attrs, $log, $http) {
    $log.log("[ctrl-model-svg]: wurde initialisiert");

    $scope.TPS_Config = 0;

    $log.log("[ctrl-model-svg]: lade TPS config");
    $http.get("param/Model_TestPointedSignals.json").then(function (response) {
        $scope.TPS_Config = response.data;
        $log.log($scope.TPS_Config);
    });

    $scope.$on("open-SVG", function (event, target) {
        $("#SVG_Graphic").attr("data", target);
    });

    $scope.editTPS = function () {
        // ging nicht anders, deswegen habe ich plain javascript verwendet
        let svg = document.getElementById("SVG_Graphic");
        let svgDoc = svg.contentDocument;
        $scope.TPS_Config.TestPointedSignals.forEach(function (currentValue, index, refarray) {
            let tps = svgDoc.getElementById(currentValue.id);
            if (tps !== null) {
                tps.textContent = Math.round($scope.TPS_Values.TestPointedSignals[index] * 100) / 100;
            }
        });
    };

    $scope.openBlockParam = function (filter) {
        $scope.openParams('Params', filter, true);
    };

});