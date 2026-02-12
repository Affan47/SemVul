PipelineD::buildInnerQueryExecutorGeneric(const CollectionPtr& collection,
                                          const NamespaceString& nss,
                                          const AggregateCommandRequest* aggRequest,
                                          Pipeline* pipeline) {


    pipeline->optimizePipeline();

    Pipeline::SourceContainer& sources = pipeline->_sources;
    auto expCtx = pipeline->getContext();


    const BSONObj queryObj = pipeline->getInitialQuery();
    if (!queryObj.isEmpty()) {
        auto matchStage = dynamic_cast<DocumentSourceMatch*>(sources.front().get());
        if (matchStage) {


            sources.pop_front();
        } else {


            MONGO_UNREACHABLE;
        }
    }

    auto&& [sortStage, groupStage] = getSortAndGroupStagesFromPipeline(pipeline->_sources);
    std::unique_ptr<GroupFromFirstDocumentTransformation> rewrittenGroupStage;
    if (groupStage) {
        rewrittenGroupStage = groupStage->rewriteGroupAsTransformOnFirstDocument();
    }


    const auto skipThenLimit = extractSkipAndLimitForPushdown(pipeline);

    auto unavailableMetadata = DocumentSourceMatch::isTextQuery(queryObj)
        ? DepsTracker::kDefaultUnavailableMetadata & ~DepsTracker::kOnlyTextScore
        : DepsTracker::kDefaultUnavailableMetadata;


    bool shouldProduceEmptyDocs = false;
    auto exec = uassertStatusOK(prepareExecutor(expCtx,
                                                collection,
                                                nss,
                                                pipeline,
                                                sortStage,
                                                std::move(rewrittenGroupStage),
                                                unavailableMetadata,
                                                queryObj,
                                                skipThenLimit,
                                                aggRequest,
                                                Pipeline::kAllowedMatcherFeatures,
                                                &shouldProduceEmptyDocs));

    const auto cursorType = shouldProduceEmptyDocs
        ? DocumentSourceCursor::CursorType::kEmptyDocuments
        : DocumentSourceCursor::CursorType::kRegular;


    const bool trackOplogTS =
        (pipeline->peekFront() && pipeline->peekFront()->constraints().isChangeStreamStage()) ||
        (aggRequest && aggRequest->getRequestReshardingResumeToken());

    auto attachExecutorCallback =
        [cursorType, trackOplogTS](const CollectionPtr& collection,
                                   std::unique_ptr<PlanExecutor, PlanExecutor::Deleter> exec,
                                   Pipeline* pipeline) {
            auto cursor = DocumentSourceCursor::create(
                collection, std::move(exec), pipeline->getContext(), cursorType, trackOplogTS);
            pipeline->addInitialSource(std::move(cursor));
        };
    return std::make_pair(std::move(attachExecutorCallback), std::move(exec));
}
