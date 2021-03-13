moduleSWV.controller("ctrl-model-svg", function ($scope, $attrs, $log, $http) {
    $log.log("[ctrl-model-svg]: wurde initialisiert");

    $scope.TPS_Config = 0;

    $log.log("[ctrl-model-svg]: lade TPS config");
    $http.get("param/Model_TestPointedSignals.json",{headers:{'If-Modified-Since': '0',
    "Pragma": "no-cache",
    "Expires": -1,
    "Cache-Control": "no-cache, no-store, must-revalidate"}}).then(function (response) {
        $scope.TPS_Config = response.data;
        $log.log($scope.TPS_Config);
    });

    $scope.$on("open-SVG", function (event, target) {
		var divEl = document.getElementById("content");
		divEl.innerHTML = '<object id="SVG_Graphic" data-ng-controller="ctrl-model-svg" type="image/svg+xml" data=' + target + '></object>';
		// TODO: A bit risky to directly refresh the HTML content (Non-event functions in this scope will not work). 
		// Will be improved in the future (Currently necessary to avoid the empty page problem)
    });

    $scope.$on("edit-TPS", function (event) {
		try {
			let svg = document.getElementById("SVG_Graphic");
			let svgDoc = svg.contentDocument;
			if (svgDoc !== null && typeof($scope.TPS_Config.TestPointedSignals) !== 'undefined') {
			  $scope.TPS_Config.TestPointedSignals.forEach(function (currentValue, index, refarray) {
				  let tps = svgDoc.getElementById(currentValue.id);
				  if (tps !== null && (typeof($scope.TPS_Values.TestPointedSignals) !== "undefined") && (typeof($scope.TPS_Values.TestPointedSignals[index]) !== "undefined") && (typeof($scope.TPS_Values.TestPointedSignals[index].value !== "undefined")) ) {
					  tps.textContent = $scope.TPS_Values.TestPointedSignals[index].value;
					  let rect = svgDoc.getElementById(currentValue.id + "_rect");
					  if (rect !== null) {
						  var bbox = tps.getBBox();
						  var padding = parseFloat(rect.getAttribute("padding"));
						  var w = bbox.width + 2*padding;
						  var w_initial = parseFloat(rect.getAttribute("initial-width"));
						  if (w < w_initial) {
							  w = w_initial;
						  }
						  rect.setAttribute("width",w);
					  }
				  }
			  });
			}
			else {
			  //TODO: tps not exist or undefined
			}
		}
		catch(err) {
			//TODO
		}
    });

});
