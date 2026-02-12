auto buildProjectionForPushdown(const DepsTracker& deps,
                                Pipeline* pipeline,
                                bool allowExpressions) {
    auto&& sources = pipeline->getSources();


    if (sources.empty()) {
        return BSONObj();
    }

    if (const auto projStage =
            exact_pointer_cast<DocumentSourceSingleDocumentTransformation*>(sources.front().get());
        projStage) {
        if (projStage->getType() == TransformerInterface::TransformerType::kInclusionProjection) {
            auto projObj =
                projStage->getTransformer().serializeTransformation(boost::none).toBson();
            auto projAst = projection_ast::parse(projStage->getContext(),
                                                 projObj,
                                                 ProjectionPolicies::aggregateProjectionPolicies());
            if (!projAst.hasExpressions() || allowExpressions) {

                sources.pop_front();
                return projObj;
            }
        }
    }


    if (deps.getNeedsAnyMetadata())
        return BSONObj();
    return deps.toProjectionWithoutMetadata();
}
