void ReadVariableOp::Compute(OpKernelContext* ctx) {
  core::RefCountPtr<Var> variable;
  const ResourceHandle& handle = HandleFromInput(ctx, 0);
  const auto status = LookupResource(ctx, handle, &variable);
  OP_REQUIRES(ctx, status.ok(),
              errors::FailedPrecondition(
                  "Could not find variable ", handle.name(), ". ",
                  "This could mean that the variable has been deleted. ",
                  "In TF1, it can also mean the variable is uninitialized. ",
                  "Debug info: container=", handle.container(),
                  ", status=", status.ToString()));

  tf_shared_lock ml(*variable->mu());


  const Tensor* t = variable->tensor();
  if (!variable->copy_on_read_mode.load()) {
    OP_REQUIRES(
        ctx, dtype_ == t->dtype(),
        errors::InvalidArgument(
            "Trying to read variable with wrong dtype. Expected ",
            DataTypeString(dtype_), " got ", DataTypeString(t->dtype())));
    ctx->set_output(0, *t);
  } else {
    OP_REQUIRES_OK(ctx, CopyVariable(0, ctx, t));
  }
}
