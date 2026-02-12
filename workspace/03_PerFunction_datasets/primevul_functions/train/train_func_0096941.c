boost::optional<DocumentSource::DistributedPlanLogic> DocumentSourceGroup::distributedPlanLogic() {
    intrusive_ptr<DocumentSourceGroup> mergingGroup(new DocumentSourceGroup(pExpCtx));
    mergingGroup->setDoingMerge(true);

    VariablesParseState vps = pExpCtx->variablesParseState;

    mergingGroup->setIdExpression(ExpressionFieldPath::parse(pExpCtx.get(), "$$ROOT._id", vps));

    for (auto&& accumulatedField : _accumulatedFields) {


        auto copiedAccumulatedField = accumulatedField;
        copiedAccumulatedField.expr.argument = ExpressionFieldPath::parse(
            pExpCtx.get(), "$$ROOT." + copiedAccumulatedField.fieldName, vps);
        mergingGroup->addAccumulator(copiedAccumulatedField);
        mergingGroup->_memoryTracker.set(copiedAccumulatedField.fieldName, 0);
    }


    return DistributedPlanLogic{this, mergingGroup, boost::none};
}
