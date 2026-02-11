IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "PreshadeColorCtl") {
        if (tag->hasChildren())
            setPreshadeCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "RuntimeColorCtl") {
        if (tag->hasChildren())
            setRuntimeCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "AmbientColorCtl") {
        if (tag->hasChildren())
            setAmbientCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "SpecularColorCtl") {
        if (tag->hasChildren())
            setSpecularCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "OpacityCtl") {
        if (tag->hasChildren())
            setOpacityCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "TransformCtl") {
        if (tag->hasChildren())
            setTransformCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plLayerInterface::IPrcParse(tag, mgr);
    }
}
