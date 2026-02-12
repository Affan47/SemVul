Status LocalEagerCopyToDevice(TensorHandle* h, EagerContext* ctx,
                              EagerExecutor* executor, Device* dstd,
                              bool mirror, TensorHandle** result) {
  TF_RETURN_IF_ERROR(executor->status());
  Device* d = ctx->CanonicalDevice(dstd);
  if (mirror && h->HasLocalMirror(d)) {
    h->Ref();
    *result = h;
    return Status::OK();
  }

  bool async = executor->Async();
  if (mirror) {
    h->Ref();
    *result = h;

    if (h->HasLocalMirror(d)) {
      return Status::OK();
    }


    if (async) {
      Status s = h->AddEmptyLocalMirror(d);
      if (!s.ok()) {


        if (s.code() == error::Code::ALREADY_EXISTS) {
          return Status::OK();
        }


        h->Unref();
        *result = nullptr;
        return s;
      }
    }
  } else {
    *result = TensorHandle::CreateEmptyLocalHandle(
        d, dstd, h->resource_device(), h->dtype, ctx);
  }

  Status s;
  if (async) {


    std::unique_ptr<EagerNode> node(
        new CopyToDeviceNode(h, *result, d, *ctx, async, mirror));
    s = executor->AddOrExecute(std::move(node));
  } else {
    CopyToDeviceNode node(h, *result, d, *ctx, async, mirror);
    s = executor->SyncExecute(&node);
  }


  if (!s.ok()) {
    (*result)->Unref();
    *result = nullptr;
  }

  return s;
}
