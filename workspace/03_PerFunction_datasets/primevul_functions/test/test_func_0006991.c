void QuantizeTensor(OpKernelContext* ctx, const Tensor& input,
                      const float input_min_range, const float input_max_range,
                      Tensor* output, Tensor* output_min_tensor,
                      Tensor* output_max_tensor) {
    OP_REQUIRES(ctx, !(input_max_range < input_min_range),
                errors::InvalidArgument(
                    "input_max_range must be larger than input_min_range."));


    float min_range = std::min(0.0f, input_min_range);
    const float epsilon = std::max(1.0f, std::max(fabsf(input_min_range),
                                                  fabsf(input_max_range))) *
                          ensure_minimum_range_;
    float max_range =
        std::max(0.0f, std::max(input_max_range, min_range + epsilon));

    if (mode_ == QUANTIZE_MODE_MIN_FIRST) {
      if (meta::IsSupportedAndEnabled() && std::is_same<T, quint8>()) {
        TTypes<const float>::Vec input_array = input.flat<float>();

        meta::Quantize(ctx, input_array.data(), input_array.size(), min_range,
                       max_range, output->flat<quint8>().data());
      } else {
        FloatTensorToQuantizedInPlaceUsingEigen<T>(
            ctx->template eigen_device<Device>(), input, min_range, max_range,
            output);
      }
      output_min_tensor->flat<float>()(0) = min_range;
      output_max_tensor->flat<float>()(0) = max_range;
    } else {
      QuantizeSlice(ctx->eigen_device<Device>(), ctx, input.flat<float>(),
                    input_min_range, input_max_range,
                    output->template flat<T>(),
                    &output_min_tensor->flat<float>()(0),
                    &output_max_tensor->flat<float>()(0));
    }
  }
