TfLiteStatus Subgraph::AllocateTensors() {
  TFLITE_SCOPED_TAGGED_DEFAULT_PROFILE(profiler_.get(), "AllocateTensors");

  if (!consistent_) {
    ReportError("AllocateTensors() called on inconsistent model.");
    return kTfLiteError;
  }


  TF_LITE_ENSURE_STATUS(RedoAllDelegates());


  if (state_ != kStateUninvokable &&
      !HasDynamicTensorImpl(context_, inputs())) {
    if (memory_planner_ && !memory_planner_->HasNonPersistentMemory()) {


      memory_planner_->AcquireNonPersistentMemory();
    }
    return kTfLiteOk;
  }


  SubgraphGuard guard(&context_, &is_subgraph_in_use_);
  TF_LITE_ENSURE_OK(&context_, guard.status());

  next_execution_plan_index_to_prepare_ = 0;
  next_execution_plan_index_to_plan_allocation_ = 0;
  next_original_execution_plan_index_to_prepare_ = 0;
  if (memory_planner_) {
    TF_LITE_ENSURE_STATUS(memory_planner_->ResetAllocations());
  }

  TF_LITE_ENSURE_STATUS(PrepareOpsAndTensors());

  state_ = kStateInvokable;


  ResetVariableTensors();

  return kTfLiteOk;
}
