void Compute(OpKernelContext* context) override {
    const auto& input = context->input(0);
    auto flat_in = input.flat<tstring>();

    int fixed_length;
    const auto& length_input = context->input(1);
    OP_REQUIRES(context, TensorShapeUtils::IsScalar(length_input.shape()),
                errors::InvalidArgument("k must be scalar, got shape ",
                                        length_input.shape().DebugString()));
    fixed_length = length_input.scalar<int32>()();

    OP_REQUIRES(
        context, fixed_length % sizeof(T) == 0,
        errors::InvalidArgument(
            "fixed_length (", fixed_length,
            ") must be a multiple of the size of out_type (", sizeof(T), ")"));

    OP_REQUIRES(context, fixed_length > 0,
                errors::InvalidArgument("fixed_length (", fixed_length,
                                        ") must be greater than zero."));

    int width = fixed_length / sizeof(T);

    TensorShape out_shape = input.shape();
    out_shape.AddDim(width);
    Tensor* output_tensor = nullptr;
    OP_REQUIRES_OK(
        context, context->allocate_output("output", out_shape, &output_tensor));

    if (flat_in.size() == 0) {
      return;
    }

    auto out = output_tensor->flat_inner_dims<T>();
    T* out_data = out.data();


    memset(out_data, 0, fixed_length * flat_in.size());


    if (!convert_data_endianness_ || sizeof(T) == 1) {
      for (int64 i = 0; i < flat_in.size(); ++i) {
        const auto to_copy =
            std::min(flat_in(i).size(), static_cast<size_t>(fixed_length));
        memcpy(out_data, flat_in(i).data(), to_copy);


        out_data += width;
      }
    } else {


      for (int64 i = 0; i < flat_in.size(); ++i) {
        const char* in_data_bytes =
            reinterpret_cast<const char*>(flat_in(i).data());
        char* out_data_bytes = reinterpret_cast<char*>(out_data);
        const char* p_in = in_data_bytes;
        char* p_out = out_data_bytes;
        for (; p_in < in_data_bytes + fixed_length;
             p_in += sizeof(T), p_out += sizeof(T)) {
          std::reverse_copy(p_in, p_in + sizeof(T), p_out);
        }


        out_data += width;
      }
    }
  }
