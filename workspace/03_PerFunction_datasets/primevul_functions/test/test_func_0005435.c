void Compute(OpKernelContext* context) override {
    const Tensor& value = context->input(1);
    core::RefCountPtr<Var> variable;
    OP_REQUIRES_OK(context, LookupOrCreateResource<Var>(
                                context, HandleFromInput(context, 0), &variable,
                                [](Var** ptr) {

                                  *ptr = new Var(DT_VARIANT);
                                  return Status::OK();
                                }));


    AllocatorAttributes attr;


    std::unique_ptr<Tensor> input_alias = context->forward_input(
        1, OpKernelContext::Params::kNoReservation , DT_VARIANT,
        value.shape(),
        DEVICE_MEMORY ,
        attr);

    mutex_lock ml(*variable->mu());
    OP_REQUIRES(context, variable->tensor()->dtype() == DT_VARIANT,
                errors::InvalidArgument(
                    "Trying to assign variable with wrong dtype. Expected ",
                    DataTypeString(variable->tensor()->dtype()), " got ",
                    DataTypeString(DT_VARIANT)));
    variable->is_initialized = true;
    *variable->tensor() = Tensor(DT_VARIANT, value.shape());

    if (input_alias) {
      *variable->tensor() = *input_alias;
      return;
    }


    if (!variable->tensor()->RefCountIsOne() ||
        !variable->tensor()->shape().IsSameSize(value.shape())) {

      attr.set_on_host(true);
      OP_REQUIRES_OK(context, context->allocate_temp(DT_VARIANT, value.shape(),
                                                     variable->tensor(), attr));
    }

    const auto elements_in = value.flat<Variant>();
    auto elements_out = variable->tensor()->flat<Variant>();
    for (int64_t i = 0; i < elements_in.size(); ++i) {
      elements_out(i) = elements_in(i);
    }
  }
