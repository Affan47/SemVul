Status GetOrCreateKernelAndDevice(
    EagerOperation* op, TensorHandle** retvals, int* num_retvals,
    core::RefCountPtr<KernelAndDevice>* out_kernel) {
  EagerContext& ctx = op->EagerContext();
  Device* device = absl::get<Device*>(op->Device());


  if (device == nullptr && !op->is_function()) {
    Fprint128 device_cache_key = GetDeviceCacheKey(op, ctx);
    device = ctx.GetCachedDevice(device_cache_key);
    if (device == nullptr) {
      TF_RETURN_IF_ERROR(SetOpDevice(ctx, op, &device));
      ctx.AddDeviceToCache(device_cache_key, device);
    } else {
      op->SetDevice(device);
    }
  }


  bool reuse_rendezvous_for_functions_original_value =
      ctx.GetReuseRendezvousForFunctions();


  bool reuse_rendezvous_for_functions =
      (ctx.RunEagerOpAsFunction() && !op->is_function()) ||
      reuse_rendezvous_for_functions_original_value;

  std::vector<Device*> input_dev_ptrs;
  absl::flat_hash_map<string, const std::vector<string>*> composite_devices;
  std::unordered_map<int, DtypeAndPartialTensorShape>
      input_resource_variable_dtypes_and_shapes;
  if (op->is_function() || ctx.RunEagerOpAsFunction()) {
    profiler::TraceMe activity("EagerCopyToDevice",
                               profiler::TraceMeLevel::kInfo);
    input_dev_ptrs.reserve(op->Inputs().size());
    const absl::InlinedVector<TensorHandle*, 4>* inputs;
    TF_RETURN_IF_ERROR(op->TensorHandleInputs(&inputs));
    for (int i = 0, end = inputs->size(); i < end; ++i) {
      TensorHandle* input = (*inputs)[i];

      Device* input_device;
      TF_RETURN_IF_ERROR(GetDeviceForInput(*op, ctx, input, &input_device));
      VLOG(1) << op->Name() << ":input:" << i << " " << input_device->name();
      input_dev_ptrs.push_back(input_device);
      CompositeDevice* composite_device = nullptr;
      if (ctx.FindCompositeDeviceFromName(input_device->name(),
                                          &composite_device)
              .ok()) {
        composite_devices[input_device->name()] =
            composite_device->underlying_devices();
      }
      if (input->dtype == DT_RESOURCE) {


        std::vector<DtypeAndPartialTensorShape> resource_dtypes_and_shapes;
        TF_RETURN_IF_ERROR(input->GetResourceHandleDtypesAndShapes(
            &resource_dtypes_and_shapes));
        if (!resource_dtypes_and_shapes.empty()) {
          const DtypeAndPartialTensorShape& dtype_and_shape =
              resource_dtypes_and_shapes.at(0);
          input_resource_variable_dtypes_and_shapes[i] = dtype_and_shape;
        }
      }
    }
  }

  TF_ASSIGN_OR_RETURN(
      Fprint128 cache_key,
      GetKernelCacheKey(*op, op->MutableAttrs()->CacheKey(op->DeviceName()),
                        input_dev_ptrs,
                        input_resource_variable_dtypes_and_shapes));
  core::RefCountPtr<KernelAndDevice> kernel = ctx.GetCachedKernel(cache_key);
  AbstractOperationPtr wrapped_op_releaser;


  if (kernel == nullptr) {
    VLOG(2) << "Creating new kernel for " << op->Name() << " on device "
            << DeviceNameOrUnspecified(absl::get<Device*>(op->Device()));
    bool run_function_with_flr = false;
    bool function_outputs_on_op_device = false;
    absl::optional<string> xla_compile_device_type;
    if (op->is_function()) {
      bool compile_with_xla;
      TF_RETURN_IF_ERROR(MustCompileWithXLA(op, ctx, &compile_with_xla));
      if (compile_with_xla) {
        if (ctx.JitCompileRewrite()) {
          xla_compile_device_type = op->GetDeviceParsedName().type;
          run_function_with_flr = true;
        } else {


          op->MutableAttrs()->Set(kXlaMustCompileAttr, true);
        }
      } else {
        run_function_with_flr = true;
      }
      GetFuncAttr(op, ctx, kOutputsOnOpDevice, &function_outputs_on_op_device)
          .IgnoreError();
    }

    VLOG(2) << op->Name() << " function_outputs_on_op_device: "
            << function_outputs_on_op_device;
    if (device == nullptr) {
      TF_RETURN_IF_ERROR(SetOpDevice(ctx, op, &device));
    } else {
      VLOG(1) << "Device for [" << op->Name()
              << "] already set to: " << device->name();
    }


    bool allow_small_function_optimizations = false;
    bool int_args_and_retvals_on_device = false;
    bool allow_control_flow_sync_execution = false;


    bool shape_inference_on_tfe_dialect_import = true;
    if (ctx.RunEagerOpAsFunction() && !op->is_function()) {
      EagerOperation* wrapped_op = nullptr;
      TF_RETURN_IF_ERROR(ValidateOp(op));
      TF_RETURN_IF_ERROR(WrapInCallOp(op, &wrapped_op));
      DCHECK(wrapped_op);
      DCHECK(wrapped_op->is_function());
      wrapped_op_releaser.reset(wrapped_op);
      run_function_with_flr = true;
      allow_small_function_optimizations = true;
      allow_control_flow_sync_execution = true;
      shape_inference_on_tfe_dialect_import = false;
      int_args_and_retvals_on_device = IntArgsAndRetvalsOnDevice(op);
      op = wrapped_op;
    }
    const NodeDef& ndef = op->MutableAttrs()->BuildNodeDef();

    FunctionLibraryRuntime* flr =
        device == nullptr ? nullptr : ctx.func_lib(device);
    if (device != nullptr && flr == nullptr) {
      return errors::NotFound(
          "Unable to find a FunctionLibraryRuntime corresponding to device ",
          device->name());
    }
    auto runner = (flr != nullptr && flr->runner() != nullptr) ? flr->runner()
                                                               : ctx.runner();
    GraphCollector* graph_collector = nullptr;
    if (ctx.ShouldStoreGraphs()) {
      graph_collector = ctx.GetGraphCollector();
    }


    if (run_function_with_flr) {


      VLOG(2) << "Running " << ndef.op() << " using multi-device function. "
              << "Full node_def=" << ndef.DebugString();
      std::function<int64_t()> get_op_id = nullptr;
#if !defined(IS_MOBILE_PLATFORM)
      get_op_id = [&ctx]() { return ctx.RemoteMgr()->NextOpId(); };
#endif

      ctx.reuse_rendezvous_for_functions_mu()->lock();
      ctx.SetReuseRendezvousForFunctions(reuse_rendezvous_for_functions);
      auto rendezvous_creator = ctx.RendezvousCreator();
      ctx.SetReuseRendezvousForFunctions(
          reuse_rendezvous_for_functions_original_value);
      ctx.reuse_rendezvous_for_functions_mu()->unlock();
      kernel.reset(new KernelAndDeviceFunc(
          flr, ctx.pflr(), std::move(input_dev_ptrs),
          std::move(composite_devices),
          std::move(input_resource_variable_dtypes_and_shapes), runner,
          ctx.GetCollectiveExecutorHandle(), ctx.HostCPU(), op->Name(),
          function_outputs_on_op_device, allow_small_function_optimizations,
          allow_control_flow_sync_execution,
          shape_inference_on_tfe_dialect_import, int_args_and_retvals_on_device,
          xla_compile_device_type, std::move(rendezvous_creator), get_op_id));
    } else {
      VLOG(2) << "Running " << ndef.op() << " using op kernel. "
              << ". Full node_def=" << ndef.DebugString();
      kernel.reset(new KernelAndDeviceOp(
          ctx.GetRendezvous(), ctx.LogMemory(), flr, runner,
          ctx.GetCollectiveExecutorHandle(), ctx.HostCPU()));
    }

    TF_RETURN_IF_ERROR(
        kernel->Init(ctx.LogDevicePlacement(), ndef, graph_collector));

    if (op->is_function()) {
      ctx.AddKernelToCache(cache_key, kernel.get());
    } else {


      const OpDef* op_def;
      TF_RETURN_IF_ERROR(OpDefForOp(op->Name().data(), &op_def));
      if (KernelCacheEnabled(*op_def)) {
        ctx.AddKernelToCache(cache_key, kernel.get());
      }
    }
  }

  int num_outputs = kernel->num_outputs();
  if (num_outputs > *num_retvals) {
    return errors::InvalidArgument("Expecting ", num_outputs,
                                   " outputs, but *num_retvals is ",
                                   *num_retvals);
  }
  *num_retvals = num_outputs;

  kernel->Ref();
  out_kernel->reset(kernel.get());
  return Status::OK();
}
