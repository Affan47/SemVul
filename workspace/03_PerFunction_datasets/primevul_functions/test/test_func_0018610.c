boost::optional<long long> extractSkipForPushdown(Pipeline* pipeline) {


    if (MONGO_unlikely(disablePipelineOptimization.shouldFail())) {
        return boost::none;
    }
    auto&& sources = pipeline->getSources();

    auto skip = extractSkipForPushdown(sources.begin(), &sources);
    if (skip) {

        pipeline->optimizePipeline();
    }
    return skip;
}
