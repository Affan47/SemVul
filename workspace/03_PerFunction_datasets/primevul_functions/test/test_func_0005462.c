explicit ResourceScatterUpdateOp(OpKernelConstruction* c) : OpKernel(c) {


    Status s = c->GetAttr("use_locking", &use_exclusive_lock_);
    if (!s.ok()) {
      use_exclusive_lock_ = false;
    }
  }
