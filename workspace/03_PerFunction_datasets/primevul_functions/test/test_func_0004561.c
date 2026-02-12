void DocumentSourceUnionWith::reattachToOperationContext(OperationContext* opCtx) {


    if (_pipeline) {
        _pipeline->reattachToOperationContext(opCtx);
    }
}
