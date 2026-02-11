defaultViewLayerPlacement(ModelPart * modelPart) {
    if (modelPart == NULL || boardLayers() == 2) return SketchWidget::defaultViewLayerPlacement(modelPart);

    if (modelPart->flippedSMD()) return ViewLayer::NewBottom;
    if (modelPart->moduleID() == ModuleIDNames::GroundPlaneModuleIDName) return ViewLayer::NewBottom;

    return SketchWidget::defaultViewLayerPlacement(modelPart);
}
