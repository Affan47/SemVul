void Compute(OpKernelContext* ctx) override {
    Tensor* out = nullptr;


    AllocatorAttributes attr;
    attr.set_gpu_compatible(true);
    OP_REQUIRES_OK(ctx, ctx->allocate_output(0, shape_, &out, attr));
  }
