DocumentSource::GetNextResult DocumentSourceUnionWith::doGetNext() {
    if (!_pipeline) {

        return GetNextResult::makeEOF();
    }

    if (_executionState == ExecutionProgress::kIteratingSource) {
        auto nextInput = pSource->getNext();
        if (!nextInput.isEOF()) {
            return nextInput;
        }
        _executionState = ExecutionProgress::kStartingSubPipeline;


    }

    if (_executionState == ExecutionProgress::kStartingSubPipeline) {
        auto serializedPipe = _pipeline->serializeToBson();


        if (pExpCtx->variables.hasConstantValue(Variables::kSearchMetaId)) {
            _pipeline->getContext()->variables.setReservedValue(
                Variables::kSearchMetaId,
                pExpCtx->variables.getValue(Variables::kSearchMetaId, Document()),
                true);
        }
        logStartingSubPipeline(serializedPipe);
        try {
            _pipeline =
                pExpCtx->mongoProcessInterface->attachCursorSourceToPipeline(_pipeline.release());
            _executionState = ExecutionProgress::kIteratingSubPipeline;
        } catch (const ExceptionFor<ErrorCodes::CommandOnShardedViewNotSupportedOnMongod>& e) {
            _pipeline = buildPipelineFromViewDefinition(
                pExpCtx,
                ExpressionContext::ResolvedNamespace{e->getNamespace(), e->getPipeline()},
                serializedPipe);
            logShardedViewFound(e);
            return doGetNext();
        }
    }

    auto res = _pipeline->getNext();
    if (res)
        return std::move(*res);


    recordPlanSummaryStats(*_pipeline);

    _executionState = ExecutionProgress::kFinished;
    return GetNextResult::makeEOF();
}
