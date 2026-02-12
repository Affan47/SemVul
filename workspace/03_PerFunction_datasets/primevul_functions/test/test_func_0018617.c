void PipelineD::attachInnerQueryExecutorToPipeline(
    const CollectionPtr& collection,
    PipelineD::AttachExecutorCallback attachExecutorCallback,
    std::unique_ptr<PlanExecutor, PlanExecutor::Deleter> exec,
    Pipeline* pipeline) {


    if (attachExecutorCallback && exec) {
        attachExecutorCallback(collection, std::move(exec), pipeline);
    }
}
