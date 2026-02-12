Status EagerCopyToDevice(TensorHandle* h, EagerContext* ctx,
                         EagerExecutor* executor, Device* device, bool mirror,
                         TensorHandle** result) {
  TF_RETURN_IF_ERROR(h->WaitUnknownDevice());
  auto send_device = h->DeviceOrHostCPU(*ctx);
  bool sender_is_local = send_device->IsLocal();

  bool receiver_is_local = device->IsLocal();

  if (!executor->Async()) {


    executor->ClearError();
  }

  if (sender_is_local && receiver_is_local) {
    return LocalEagerCopyToDevice(h, ctx, executor, device, mirror, result);
  } else {
#if defined(IS_MOBILE_PLATFORM)
    return errors::Unimplemented(
        "Eager's remote execution is not available on mobile devices.");
#else
    uint64 recv_op_id = 0;
    if (receiver_is_local) {
      Device* d = ctx->CanonicalDevice(device);


      if (mirror) {
        h->Ref();
        *result = h;

        if (h->HasLocalMirror(d)) {
          return Status::OK();
        }

        Status s = h->AddEmptyLocalMirror(d);
        if (!s.ok()) {


          if (s.code() == error::Code::ALREADY_EXISTS) {
            return Status::OK();
          }


          h->Unref();
          *result = nullptr;
          return s;
        }
      } else {
        *result = TensorHandle::CreateEmptyLocalHandle(
             d,  device,
            nullptr, h->dtype, ctx);
      }
    } else {
      if (mirror) {
        if (h->HasRemoteMirror(device, ctx->GetContextViewId())) {
          h->Ref();
          *result = h;
          return Status::OK();
        }
      }
      string remote_task;
      if (!DeviceNameUtils::GetTaskName(device->parsed_name(), &remote_task)) {
        return errors::InvalidArgument(
            "Unable to find remote task corresponding to device ",
            device->name());
      }
      recv_op_id = ctx->RemoteMgr()->NextOpId();
      if (mirror) {
        TF_RETURN_IF_ERROR(h->AddUnshapedRemoteMirror(device, recv_op_id, 0,
                                                      remote_task, ctx));
        h->Ref();
        *result = h;
      } else {
        *result = TensorHandle::CreateUnshapedRemoteHandle(
            recv_op_id, 0, remote_task, h->dtype, device, ctx);
      }
    }

    auto node = std::make_unique<eager::RemoteCopyNode>(
        ctx, executor, h, result[0], device, recv_op_id);
    Status s = executor->AddOrExecute(std::move(node));
    if (!s.ok()) {
      result[0]->Unref();
      result[0] = nullptr;
    }
    return s;
#endif
  }
}
