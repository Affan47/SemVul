void ExpressionMeta::_doAddDependencies(DepsTracker* deps) const {
    if (_metaType == MetaType::kSearchScore || _metaType == MetaType::kSearchHighlights) {


        return;
    }

    deps->setNeedsMetadata(_metaType, true);
}
