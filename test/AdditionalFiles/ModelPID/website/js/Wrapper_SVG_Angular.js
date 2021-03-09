function WrapperSvgAngular(BlockInfo) {
    let scope = angular.element($("#SVG_Graphic")).scope();
    scope.openBlockParam(BlockInfo);
}

function WrapperOpenSvg(Subsystem) {
    let scope = angular.element($("#Page")).scope();
    scope.openSvg(Subsystem);
}

function WrapperOpenTrace(nameOfConfig) {
    let scope = angular.element($("#Page")).scope();
    scope.openTrace(nameOfConfig);
}
