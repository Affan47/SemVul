StatusWith<std::unique_ptr<PlanExecutor, PlanExecutor::Deleter>> PipelineD::prepareExecutor(
    const intrusive_ptr<ExpressionContext>& expCtx,
    const CollectionPtr& collection,
    const NamespaceString& nss,
    Pipeline* pipeline,
    const boost::intrusive_ptr<DocumentSourceSort>& sortStage,
    std::unique_ptr<GroupFromFirstDocumentTransformation> rewrittenGroupStage,
    QueryMetadataBitSet unavailableMetadata,
    const BSONObj& queryObj,
    SkipThenLimit skipThenLimit,
    const AggregateCommandRequest* aggRequest,
    const MatchExpressionParser::AllowedFeatureSet& matcherFeatures,
    bool* hasNoRequirements) {
    invariant(hasNoRequirements);


    size_t plannerOpts = QueryPlannerParams::DEFAULT;

    if (pipeline->peekFront() && pipeline->peekFront()->constraints().isChangeStreamStage()) {
        invariant(expCtx->tailableMode == TailableModeEnum::kTailableAndAwaitData);
        plannerOpts |= (QueryPlannerParams::TRACK_LATEST_OPLOG_TS |
                        QueryPlannerParams::ASSERT_MIN_TS_HAS_NOT_FALLEN_OFF_OPLOG);
    }


    if (aggRequest && aggRequest->getRequestReshardingResumeToken()) {
        plannerOpts |= (QueryPlannerParams::TRACK_LATEST_OPLOG_TS |
                        QueryPlannerParams::ASSERT_MIN_TS_HAS_NOT_FALLEN_OFF_OPLOG);
    }


    BSONObj sortObj;
    if (sortStage) {
        sortObj = sortStage->getSortKeyPattern()
                      .serialize(SortPattern::SortKeySerialization::kForPipelineSerialization)
                      .toBson();

        pipeline->popFrontWithName(DocumentSourceSort::kStageName);


        invariant(!skipThenLimit.getLimit());
        invariant(!skipThenLimit.getSkip());


        auto skip = extractSkipForPushdown(pipeline);


        skipThenLimit = LimitThenSkip(sortStage->getLimit(), skip).flip();
    }


    auto deps = pipeline->getDependencies(unavailableMetadata);
    *hasNoRequirements = deps.hasNoRequirements();

    BSONObj projObj;
    if (*hasNoRequirements) {


        plannerOpts |= QueryPlannerParams::IS_COUNT;
    } else {


        bool allowExpressions = !sortStage && !skipThenLimit.getSkip() && !skipThenLimit.getLimit();
        projObj = buildProjectionForPushdown(deps, pipeline, allowExpressions);
        plannerOpts |= QueryPlannerParams::RETURN_OWNED_DATA;
    }

    if (rewrittenGroupStage) {


        auto swExecutorGrouped = attemptToGetExecutor(expCtx,
                                                      collection,
                                                      nss,
                                                      queryObj,
                                                      projObj,
                                                      deps.metadataDeps(),
                                                      sortObj,
                                                      SkipThenLimit{boost::none, boost::none},
                                                      rewrittenGroupStage->groupId(),
                                                      aggRequest,
                                                      plannerOpts,
                                                      matcherFeatures);

        if (swExecutorGrouped.isOK()) {


            invariant(!sortStage || !sortStage->hasLimit());


            pipeline->popFrontWithName(DocumentSourceSort::kStageName);
            pipeline->popFrontWithName(DocumentSourceGroup::kStageName);

            boost::intrusive_ptr<DocumentSource> groupTransform(
                new DocumentSourceSingleDocumentTransformation(
                    expCtx,
                    std::move(rewrittenGroupStage),
                    "$groupByDistinctScan",
                    false ));
            pipeline->addInitialSource(groupTransform);

            return swExecutorGrouped;
        } else if (swExecutorGrouped != ErrorCodes::NoQueryExecutionPlans) {
            return swExecutorGrouped.getStatus().withContext(
                "Failed to determine whether query system can provide a "
                "DISTINCT_SCAN grouping");
        }
    }

    return attemptToGetExecutor(expCtx,
                                collection,
                                nss,
                                queryObj,
                                projObj,
                                deps.metadataDeps(),
                                sortObj,
                                skipThenLimit,
                                boost::none,
                                aggRequest,
                                plannerOpts,
                                matcherFeatures);
}
