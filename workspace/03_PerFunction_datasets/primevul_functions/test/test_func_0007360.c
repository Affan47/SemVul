static Status StrideOrInflate(OpKernelContext* ctx, const Tensor& input,
                                const Labels& labels,
                                const LabelCounts& label_counts,
                                const bool should_inflate, Tensor* output) {

    if (absl::c_all_of(label_counts, [](int c) { return c <= 1; })) {
      return CopyFrom(input, input.shape(), output);
    }


    ShapeVec reshape;
    ShapeVec strides;


    ShapeVec strided_shape;
    ShapeVec inflated_shape;
    for (int label : labels) {
      const int count = label_counts[label];
      const int current_axis =
          should_inflate ? strided_shape.size() : inflated_shape.size();
      const int64_t dim = input.dim_size(current_axis);
      strided_shape.push_back(dim);
      inflated_shape.insert(inflated_shape.end(), count, dim);
      const int64_t reshape_dim = MathUtil::IPow(dim, count);
      reshape.push_back(reshape_dim);


      const int64_t stride =
          (dim > 1 && count > 1) ? (reshape_dim - 1) / (dim - 1) : 1;
      strides.push_back(stride);
    }

    TensorShape output_shape =
        TensorShape(should_inflate ? inflated_shape : strided_shape);
    TF_RETURN_IF_ERROR(
        ctx->allocate_temp(DataTypeToEnum<T>::value, output_shape, output));
    const Device& device = ctx->eigen_device<Device>();
    switch (reshape.size()) {
#define NDIMS_CASE(N)                                                 \
  case N: {                                                           \
    if (should_inflate) {                                             \
      auto output_map = output->shaped<T, N>(reshape);                \
      auto input_map = input.shaped<T, N>(strided_shape);             \
      functor::InflateFunctor<Device, T, N>()(                        \
          device, input_map, TensorShape(strides).AsEigenDSizes<N>(), \
          output_map);                                                \
    } else {                                                          \
      auto input_map = input.shaped<T, N>(reshape);                   \
      auto output_map = output->shaped<T, N>(strided_shape);          \
      functor::StrideFunctor<Device, T, N>()(                         \
          device, input_map, TensorShape(strides).AsEigenDSizes<N>(), \
          output_map);                                                \
    }                                                                 \
  } break;
      NDIMS_CASE(1);
      NDIMS_CASE(2);
      NDIMS_CASE(3);
      NDIMS_CASE(4);
      NDIMS_CASE(5);
      NDIMS_CASE(6);
      default:
        return errors::Unimplemented(
            "Unsupported rank: ", reshape.size(),
            " while handling repeated indices. Up to rank 6 is supported.");
#undef NDIMS_CASE
    }
    return Status::OK();
  }
