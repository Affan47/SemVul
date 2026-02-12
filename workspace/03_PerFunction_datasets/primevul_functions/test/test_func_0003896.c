Status EagerRemoteExecute(EagerOperation* op, TensorHandle** retvals,
                          int* num_retvals) {
  EagerContext& ctx = op->EagerContext();


  if (op->Device() == kVariantDeviceNull) {
    tensorflow::Device* device = nullptr;
    string device_name = op->DeviceName();
    TF_RETURN_IF_ERROR(ctx.FindDeviceFromName(device_name.c_str(), &device));
    op->SetDevice(device);
  }

  core::RefCountPtr<eager::EagerClient> eager_client;
  uint64 context_id = ctx.GetContextId();
  TF_RETURN_IF_ERROR(ctx.GetClient(op->GetDeviceParsedName(), &eager_client));
  string remote_task;
  if (!DeviceNameUtils::GetTaskName(op->GetDeviceParsedName(), &remote_task)) {
    return errors::InvalidArgument(
        "Unable to find remote task corresponding to device ",
        op->DeviceName());
  }

  std::unique_ptr<eager::EnqueueRequest> request(new eager::EnqueueRequest);
  request->set_context_id(context_id);

  eager::Operation* remote_op = request->add_queue()->mutable_operation();

  tensorflow::Device* op_device = absl::get<Device*>(op->Device());
  {
    profiler::TraceMe activity("CopyInputToExpectedDevice",
                               profiler::TraceMeLevel::kInfo);
    const bool is_function = op->is_function();
    const absl::InlinedVector<TensorHandle*, 4>* inputs;
    TF_RETURN_IF_ERROR(op->TensorHandleInputs(&inputs));
    for (int i = 0, end = inputs->size(); i < end; i++) {
      tensorflow::TensorHandle* input = (*inputs)[i];
      tensorflow::Device* input_device = input->device();
      tensorflow::Device* input_device_or_cpu = input->DeviceOrHostCPU(ctx);
      const string* input_device_name = &input_device_or_cpu->name();
      bool serialize_resource_dtype_and_shape = false;
      if (op_device != input_device &&


          !ctx.OnSameTask(op_device, input_device)) {
        if (!is_function || input_device_or_cpu->IsLocal()) {
          tensorflow::Device* remote_cpu_device;
          TF_RETURN_IF_ERROR(
              ctx.CPUDeviceOnTask(op_device, &remote_cpu_device));


          TensorHandle* handle = input;
          Device* handle_device = handle->DeviceOrHostCPU(ctx);

          if (remote_cpu_device != handle_device) {
            VLOG(6) << "remote_cpu_device != handle_device";
            TF_RETURN_IF_ERROR(CopyInputToExpectedDevice(
                &ctx, op, op_device, handle, i, handle_device,
                remote_cpu_device, &handle));
            op->UpdateInput(i, handle);
            input = handle;
            input_device = remote_cpu_device;
            input_device_name = &remote_cpu_device->name();

            handle->Unref();
          }
        } else {
          serialize_resource_dtype_and_shape =
              (input->dtype == DT_RESOURCE) &&
              (!input->HasResourceShapeMirror(op_device,
                                              ctx.GetContextViewId()));
        }
      }
      auto* input_handle = remote_op->add_op_inputs()->mutable_remote_handle();


      const bool wait_until_ready = op->is_function();
      TF_RETURN_IF_ERROR(ctx.RemoteMgr()->SerializeRemoteTensorHandle(
          input, wait_until_ready, input_handle, input_device,
          *input_device_name, serialize_resource_dtype_and_shape));
      if (!input_handle->resource_dtypes_and_shapes().empty()) {
        TF_RETURN_IF_ERROR(
            input->AddResourceShapeMirror(op_device, input_handle->op_id(),
                                          input_handle->output_num(), &ctx));
      }
    }
  }

  PrepareRemoteOp(remote_op, op);

  DataTypeVector output_dtypes;
  TF_RETURN_IF_ERROR(GetOutputDTypes(op, &output_dtypes));

  const size_t num_outputs = output_dtypes.size();
  if (num_outputs != *num_retvals) {
    return errors::InvalidArgument(
        "num_retvals does not match expected output dtypes");
  }
  *num_retvals = num_outputs;

  const tensorflow::uint64 id = remote_op->id();
  for (size_t i = 0; i < num_outputs; ++i) {


    const bool unknown_device = op->is_function();
    retvals[i] = TensorHandle::CreateUnshapedRemoteHandle(
        id, i, remote_task, output_dtypes[i], op_device, &ctx, unknown_device);
  }


  TF_RETURN_IF_ERROR(
      StoreResourceDtypesAndShapes(*remote_op, output_dtypes, retvals));

  auto& executor = op->Executor();
  VLOG(4) << "Execute remote eager op: " << op->Name()
          << " (is async?: " << executor.Async() << ").";

  const absl::InlinedVector<TensorHandle*, 4>* inputs;
  TF_RETURN_IF_ERROR(op->TensorHandleInputs(&inputs));

  std::unique_ptr<EagerNode> node(new eager::RemoteExecuteNode(
      &op->EagerContext(), std::move(request), op_device,
      ctx.GetContextViewId(), eager_client.get(), op->GetCancellationManager(),
      op->MutableAttrs()->BuildNodeDef(), op->EagerContext().FuncLibDef(),
      *inputs, {retvals, num_outputs}));

  if (op->EagerContext().LogDevicePlacement() || VLOG_IS_ON(1)) {
    string msg = strings::StrCat(
        "Executing op ", op->Name(), " on task ",
        DeviceNameUtils::ParsedNameToString(op->GetDeviceParsedName()));
    if (!logging::LogToListeners(msg)) {
      LOG(INFO) << msg;
    }
  }

  Status s = executor.AddOrExecute(std::move(node));


  if (!s.ok()) {
    for (size_t i = 0; i < num_outputs; ++i) {
      retvals[i]->Unref();


      retvals[i] = nullptr;
    }
  }

  return s;
}
