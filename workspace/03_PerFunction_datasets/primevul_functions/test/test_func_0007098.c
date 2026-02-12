boost::optional<DocumentSource::DistributedPlanLogic> DocumentSourceGroup::distributedPlanLogic() {
    intrusive_ptr<DocumentSourceGroup> mergingGroup(new DocumentSourceGroup(pExpCtx));
    mergingGroup->setDoingMerge(true);

    VariablesParseState vps = pExpCtx->variablesParseState;

    mergingGroup->setIdExpression(ExpressionFieldPath::parse(pExpCtx, "$$ROOT._id", vps));

    for (auto&& accumulatedField : _accumulatedFields) {


        auto copiedAccumulatedField = accumulatedField;
        copiedAccumulatedField.expr.argument =
            ExpressionFieldPath::parse(pExpCtx, "$$ROOT." + copiedAccumulatedField.fieldName, vps);
        mergingGroup->addAccumulator(copiedAccumulatedField);
    }


    return DistributedPlanLogic{this, mergingGroup, boost::none};
}
