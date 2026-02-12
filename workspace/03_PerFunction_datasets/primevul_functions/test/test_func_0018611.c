StatusWith<std::unique_ptr<PlanExecutor, PlanExecutor::Deleter>> attemptToGetExecutor(
    const intrusive_ptr<ExpressionContext>& expCtx,
    const CollectionPtr& collection,
    const NamespaceString& nss,
    BSONObj queryObj,
    BSONObj projectionObj,
    const QueryMetadataBitSet& metadataRequested,
    BSONObj sortObj,
    SkipThenLimit skipThenLimit,
    boost::optional<std::string> groupIdForDistinctScan,
    const AggregateCommandRequest* aggRequest,
    const size_t plannerOpts,
    const MatchExpressionParser::AllowedFeatureSet& matcherFeatures) {
    auto findCommand = std::make_unique<FindCommandRequest>(nss);
    query_request_helper::setTailableMode(expCtx->tailableMode, findCommand.get());
    findCommand->setFilter(queryObj.getOwned());
    findCommand->setProjection(projectionObj.getOwned());
    findCommand->setSort(sortObj.getOwned());
    if (auto skip = skipThenLimit.getSkip()) {
        findCommand->setSkip(static_cast<std::int64_t>(*skip));
    }
    if (auto limit = skipThenLimit.getLimit()) {
        findCommand->setLimit(static_cast<std::int64_t>(*limit));
    }

    bool isExplain = false;
    if (aggRequest) {
        findCommand->setHint(aggRequest->getHint().value_or(BSONObj()).getOwned());
        isExplain = static_cast<bool>(aggRequest->getExplain());
    }


    findCommand->setCollation(expCtx->getCollatorBSON().getOwned());

    const ExtensionsCallbackReal extensionsCallback(expCtx->opCtx, &nss);


    expCtx->sbeCompatible = true;

    auto cq = CanonicalQuery::canonicalize(expCtx->opCtx,
                                           std::move(findCommand),
                                           isExplain,
                                           expCtx,
                                           extensionsCallback,
                                           matcherFeatures,
                                           ProjectionPolicies::aggregateProjectionPolicies());

    if (!cq.isOK()) {


        return {cq.getStatus()};
    }


    cq.getValue()->requestAdditionalMetadata(metadataRequested);

    if (groupIdForDistinctScan) {


        ParsedDistinct parsedDistinct(std::move(cq.getValue()), *groupIdForDistinctScan);


        auto distinctExecutor = getExecutorDistinct(
            &collection, plannerOpts | QueryPlannerParams::STRICT_DISTINCT_ONLY, &parsedDistinct);
        if (!distinctExecutor.isOK()) {
            return distinctExecutor.getStatus().withContext(
                "Unable to use distinct scan to optimize $group stage");
        } else if (!distinctExecutor.getValue()) {
            return {ErrorCodes::NoQueryExecutionPlans,
                    "Unable to use distinct scan to optimize $group stage"};
        } else {
            return distinctExecutor;
        }
    }

    bool permitYield = true;
    return getExecutorFind(
        expCtx->opCtx, &collection, std::move(cq.getValue()), permitYield, plannerOpts);
}
