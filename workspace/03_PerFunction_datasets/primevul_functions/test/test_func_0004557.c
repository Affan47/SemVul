void DocumentSourceUnionWith::detachFromOperationContext() {


    if (_pipeline) {
        _pipeline->detachFromOperationContext();
    }
}
