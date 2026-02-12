Status EagerLocalExecute(EagerOperation* op, TensorHandle** retvals,
                         int* num_retvals) {
  profiler::ScopedMemoryDebugAnnotation op_annotation(
      op->op_name(), op->eager_func_params().has_value()
                         ? op->eager_func_params().value().step_id.value_or(0)
                         : 0);
  profiler::TraceMe activity(
      [&] { return absl::StrCat("EagerLocalExecute: ", op->Name()); },
      profiler::TraceMeLevel::kInfo);
  EagerContext& ctx = op->EagerContext();
  auto& executor = op->Executor();
  TF_RETURN_IF_ERROR(executor.status());

  core::RefCountPtr<KernelAndDevice> kernel;
  auto status = GetOrCreateKernelAndDevice(op, retvals, num_retvals, &kernel);

#ifdef INTEL_MKL
  if (IsMKLEnabled() && kernel != nullptr &&
      op->Device() == kVariantDeviceNull) {


    op->SetDevice(kernel->device());
  }
#endif


  std::unique_ptr<tensorflow::EagerOperation> out_op;
  TF_RETURN_IF_ERROR(EagerOpRewriteRegistry::Global()->RunRewrite(
      EagerOpRewriteRegistry::POST_PLACEMENT, op, &out_op));
  if (out_op) {
    op = out_op.get();


    if (op->Device() == kVariantDeviceNull) {
      status = GetOrCreateKernelAndDevice(op, retvals, num_retvals, &kernel);
    }
  }
  if (!status.ok()) return status;

  int num_outputs = kernel->num_outputs();
  TF_RETURN_IF_ERROR(ValidateInputTypeAndPlacement(&ctx, op, kernel));

  if (ctx.LogDevicePlacement() || VLOG_IS_ON(1)) {
    string msg = strings::StrCat("Executing op ", op->Name(), " in device ",
                                 kernel->device()->name());
    if (!logging::LogToListeners(msg)) {
      LOG(INFO) << msg;
    }
  }

  Status s = AddOrExecuteNode(std::move(kernel), op, retvals);


  if (!s.ok()) {
    for (int i = 0, end = num_outputs; i < end; ++i) {
      if (retvals[i] != nullptr) {
        retvals[i]->Unref();
        retvals[i] = nullptr;
      }
    }
  }

  return s;
}
