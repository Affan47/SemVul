TfLiteStatus Subgraph::ModifyGraphWithDelegate(TfLiteDelegate* delegate) {
  TFLITE_SCOPED_TAGGED_DEFAULT_PROFILE(profiler_.get(),
                                       "ModifyGraphWithDelegate");

  if (delegate == nullptr) {
    ReportError("Null delegate.");
    return kTfLiteDelegateError;
  }


  TF_LITE_ENSURE_STATUS(RedoAllDelegates());

  if (state_ == kStateInvokableAndImmutable) {
    ReportError(
        "ModifyGraphWithDelegate is disallowed when graph is immutable.");
    return kTfLiteApplicationError;
  }

  if (!(delegate->flags & kTfLiteDelegateFlagsAllowDynamicTensors)) {
    int last_execution_plan_index_prepared;
    TF_LITE_ENSURE_OK(
        &context_, PrepareOpsStartingAt(0, execution_plan_,
                                        &last_execution_plan_index_prepared));
    if (has_dynamic_tensors_) {


      TF_LITE_ENSURE_OK(&context_, EnsureMemoryAllocations());
      ReportError(
          "Attempting to use a delegate that only supports static-sized "
          "tensors with a graph that has dynamic-sized tensors.");
      return kTfLiteApplicationError;
    }
  }

  const bool was_invokable_before_delegate = state_ == kStateInvokable;
  if (delegates_applied_.empty()) {


    pre_delegation_execution_plan_ = execution_plan_;
  }


  SwitchToDelegateContext();

  auto reset_delegation_if_not_ok = [this](TfLiteStatus status) {
    if (status != kTfLiteOk) {
      TF_LITE_ENSURE_STATUS(RemoveAllDelegates());
      ReportError(
          "Restored original execution plan after delegate application "
          "failure.");
      return kTfLiteDelegateError;
    }
    return kTfLiteOk;
  };

  TfLiteStatus status = delegate->Prepare(&context_, delegate);


  SwitchToKernelContext();

  TF_LITE_ENSURE_STATUS(reset_delegation_if_not_ok(status));

  if (!(delegate->flags & kTfLiteDelegateFlagsAllowDynamicTensors)) {

    state_ = kStateUninvokable;
    TF_LITE_ENSURE_STATUS(
        reset_delegation_if_not_ok(EnsureMemoryAllocations()));


    state_ = kStateInvokableAndImmutable;
  } else if (was_invokable_before_delegate) {


    TF_LITE_ENSURE_STATUS(
        reset_delegation_if_not_ok(EnsureMemoryAllocations()));
  }
  delegates_applied_.push_back(delegate);

  return status;
}
