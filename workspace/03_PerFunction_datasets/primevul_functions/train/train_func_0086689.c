void ComputeAsync(OpKernelContext* ctx, DoneCallback done) override {


    background_worker_.Schedule([this, ctx, done = std::move(done)]() {
      OP_REQUIRES_OK_ASYNC(ctx, DoCompute(ctx), done);
      done();
    });
  }
