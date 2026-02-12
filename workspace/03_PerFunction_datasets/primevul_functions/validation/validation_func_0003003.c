void operator()(OpKernelContext* context,
                  const InputReshapedType& input_reshaped,
                  const std::vector<int64_t>& split_start_points,
                  const TensorShape& input_shape, int32_t split_dim,
                  Eigen::DenseIndex prefix_dim_size,
                  Eigen::DenseIndex split_dim_size,
                  Eigen::DenseIndex suffix_dim_size,
                  std::vector<Tlen>& split_sizes_vec,
                  const MakeSizesType& make_sizes,
                  const ReshapeResultType& reshape_result) const {
    Eigen::DSizes<Eigen::DenseIndex, NDims> indices;
    for (int i = 0; i < NDims; ++i) {
      indices[i] = 0;
    }
    const auto num_threads =
        context->device()->tensorflow_cpu_worker_threads()->num_threads;

    const auto input_element_count = input_shape.num_elements();
    const int num_split = split_start_points.size();
    const bool use_parallelism_between_outputs =
        (num_split >= kMinimumSplitNum &&
         input_element_count >= std::min(num_threads, num_split) * 4096 &&
         input_element_count < num_split * 180 * 1024);

    auto range_output_func = [&indices, context, &input_shape, split_dim,
                              &split_sizes_vec, &split_start_points,
                              use_parallelism_between_outputs, &input_reshaped,
                              &make_sizes,
                              &reshape_result](int64_t start, int64_t limit) {
      for (int64_t i = start; i < limit; ++i) {
        TensorShape output_shape(input_shape);
        output_shape.set_dim(split_dim, split_sizes_vec[i]);
        Tensor* result = nullptr;
        OP_REQUIRES_OK(context,
                       context->allocate_output(i, output_shape, &result));

        const auto sizes = make_sizes(split_sizes_vec[i]);

        if (sizes.TotalSize() > 0) {
          auto result_shaped = reshape_result(result, split_sizes_vec[i]);

          auto current_indices = indices;
          current_indices[NDims - 2] = split_start_points[i];
          if (use_parallelism_between_outputs) {

            result_shaped = input_reshaped.slice(current_indices, sizes);
          } else {

            functor::Split<CPUDevice, T, NDims>()(
                context->eigen_device<CPUDevice>(), result_shaped,
                input_reshaped, current_indices, sizes);
          }
        }
      }
    };


    if ((input_element_count >= kMinimumInputSize) &&
        input_reshaped.dimension(0) > kMinimumDim0Size && split_dim) {


      ParallelSplitByInputData(context, input_reshaped, input_shape,
                               split_sizes_vec, split_dim);
    } else if (use_parallelism_between_outputs) {


      Shard(num_split,
            context->device()->tensorflow_cpu_worker_threads()->workers,
            num_split, input_element_count / num_split, range_output_func);
    } else {

      range_output_func(0, num_split);
    }
  }
