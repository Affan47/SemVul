Value DocumentSourceUnionWith::serialize(boost::optional<ExplainOptions::Verbosity> explain) const {
    auto collectionless = _pipeline->getContext()->ns.isCollectionlessAggregateNS();
    if (explain) {


        Pipeline* pipeCopy = nullptr;
        if (*explain == ExplainOptions::Verbosity::kQueryPlanner) {
            pipeCopy = Pipeline::create(_pipeline->getSources(), _pipeline->getContext()).release();
        } else if (*explain >= ExplainOptions::Verbosity::kExecStats &&
                   _executionState > ExecutionProgress::kIteratingSource) {


            pipeCopy = Pipeline::create(_cachedPipeline, _pipeline->getContext()).release();
        } else {


            BSONArrayBuilder bab;
            for (auto&& stage : _pipeline->serialize())
                bab << stage;
            auto spec = collectionless
                ? DOC("pipeline" << bab.arr())
                : DOC("coll" << _pipeline->getContext()->ns.coll() << "pipeline" << bab.arr());
            return Value(DOC(getSourceName() << spec));
        }

        invariant(pipeCopy);
        BSONObj explainLocal =
            pExpCtx->mongoProcessInterface->preparePipelineAndExplain(pipeCopy, *explain);
        LOGV2_DEBUG(4553501, 3, "$unionWith attached cursor to pipeline for explain");

        invariant(explainLocal.nFields() == 1);

        auto spec = collectionless ? DOC("pipeline" << explainLocal.firstElement())
                                   : DOC("coll" << _pipeline->getContext()->ns.coll() << "pipeline"
                                                << explainLocal.firstElement());
        return Value(DOC(getSourceName() << spec));
    } else {
        BSONArrayBuilder bab;
        for (auto&& stage : _pipeline->serialize())
            bab << stage;
        auto spec = collectionless
            ? DOC("pipeline" << bab.arr())
            : DOC("coll" << _pipeline->getContext()->ns.coll() << "pipeline" << bab.arr());
        return Value(DOC(getSourceName() << spec));
    }
}
