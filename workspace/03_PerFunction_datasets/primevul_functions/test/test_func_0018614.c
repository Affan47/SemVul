PipelineD::buildInnerQueryExecutorSample(DocumentSourceSample* sampleStage,
                                         DocumentSourceInternalUnpackBucket* unpackBucketStage,
                                         const CollectionPtr& collection,
                                         Pipeline* pipeline) {
    tassert(5422105, "sampleStage cannot be a nullptr", sampleStage);

    auto expCtx = pipeline->getContext();

    Pipeline::SourceContainer& sources = pipeline->_sources;

    const long long sampleSize = sampleStage->getSampleSize();
    const long long numRecords = collection->getRecordStore()->numRecords(expCtx->opCtx);

    boost::optional<BucketUnpacker> bucketUnpacker;
    if (unpackBucketStage) {
        bucketUnpacker = unpackBucketStage->bucketUnpacker();
    }
    auto&& [exec, isStorageOptimizedSample] = uassertStatusOK(createRandomCursorExecutor(
        collection, expCtx, sampleSize, numRecords, std::move(bucketUnpacker)));

    AttachExecutorCallback attachExecutorCallback;
    if (exec) {
        if (!unpackBucketStage) {
            if (isStorageOptimizedSample) {

                pipeline->popFront();
                std::string idString = collection->ns().isOplog() ? "ts" : "_id";
                pipeline->addInitialSource(DocumentSourceSampleFromRandomCursor::create(
                    expCtx, sampleSize, idString, numRecords));
            }
        } else {
            if (isStorageOptimizedSample) {


                sources.erase(sources.begin());
                sources.erase(sources.begin());
            } else {


                sources.erase(sources.begin());
            }
        }


        auto deps = pipeline->getDependencies(DepsTracker::kAllMetadata);
        const auto cursorType = deps.hasNoRequirements()
            ? DocumentSourceCursor::CursorType::kEmptyDocuments
            : DocumentSourceCursor::CursorType::kRegular;
        attachExecutorCallback =
            [cursorType](const CollectionPtr& collection,
                         std::unique_ptr<PlanExecutor, PlanExecutor::Deleter> exec,
                         Pipeline* pipeline) {
                auto cursor = DocumentSourceCursor::create(
                    collection, std::move(exec), pipeline->getContext(), cursorType);
                pipeline->addInitialSource(std::move(cursor));
            };
        return std::pair(std::move(attachExecutorCallback), std::move(exec));
    }
    return std::pair(std::move(attachExecutorCallback), nullptr);
}
