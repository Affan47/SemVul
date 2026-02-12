void operator()(OpKernelContext* context, const T1* input_data,
                  int input_batches, int input_height, int input_width,
                  int input_depth, int input_offset, const T2* filter_data,
                  int filter_height, int filter_width, int filter_count,
                  int filter_offset, int stride, Padding padding,
                  T3* output_data, int output_height, int output_width,
                  int output_shift, int output_offset, int output_mult) {
    if (input_offset < 0) {

      static int warning_count = 0;
      if (warning_count < 10) {
        ++warning_count;
        LOG(WARNING)
            << "For kernel '" << context->op_kernel().name() << "' from input '"
            << context->op_kernel().requested_input(0)
            << "': Zero is not representable in the quantized range used by the"
            << " input. This means QuantizedConv2d has to fall back to a slow"
            << " implementation, since the border of zero values can't be"
            << " represented easily. You should try to construct graphs that"
            << " avoid this situation.";
      }
      ReferenceConvFunctor<T1, T2, T3> conv_functor;
      conv_functor(context, input_data, input_batches, input_height,
                   input_width, input_depth, input_offset, filter_data,
                   filter_height, filter_width, filter_count, filter_offset,
                   stride, padding, output_data, output_height, output_width,
                   output_shift, output_offset, output_mult);
      return;
    }

    OP_REQUIRES(
        context, output_width > 0,
        errors::InvalidArgument("output_width must be strictly positive"));
    OP_REQUIRES(
        context, output_height > 0,
        errors::InvalidArgument("output_height must be strictly positive"));
    int filter_left_offset;
    int filter_top_offset;
    if (padding == VALID) {
      filter_left_offset =
          ((output_width - 1) * stride + filter_width - input_width + 1) / 2;
      filter_top_offset =
          ((output_height - 1) * stride + filter_height - input_height + 1) / 2;
    } else {
      filter_left_offset =
          ((output_width - 1) * stride + filter_width - input_width) / 2;
      filter_top_offset =
          ((output_height - 1) * stride + filter_height - input_height) / 2;
    }


    const int filter_value_count = filter_width * filter_height * input_depth;
    OP_REQUIRES(context, filter_value_count > 0,
                errors::InvalidArgument(
                    "filter patch must contain at least one element"));
    const int64 patches_per_chunk =
        kMaxChunkSize / (filter_value_count * sizeof(T1));
    const int64 chunk_value_count =
        (kMaxChunkSize + (sizeof(T1) - 1)) / sizeof(T1);


    Im2ColBufferResource<T1, chunk_value_count>* im2col_buffer_resource;
    std::function<Status(Im2ColBufferResource<T1, chunk_value_count>**)>
        creator = [](Im2ColBufferResource<T1, chunk_value_count>** resource) {
#ifdef _MSC_VER


          const int64 chunk_value_count =
              (kMaxChunkSize + (sizeof(T1) - 1)) / sizeof(T1);
#endif
          *resource = new Im2ColBufferResource<T1, chunk_value_count>();
          return Status::OK();
        };
    OP_REQUIRES_OK(context, context->resource_manager()->LookupOrCreate(
                                "Conv2d", "im2col_buffer",
                                &im2col_buffer_resource, creator));


    mutex_lock lock_buffer(im2col_buffer_resource->mu);
    core::ScopedUnref unref_buffer(im2col_buffer_resource);
    T1* im2col_buffer = im2col_buffer_resource->data;

    const int64 patch_count = (input_batches * output_height * output_width);
    const int64 chunk_count =
        (patch_count + (patches_per_chunk - 1)) / patches_per_chunk;

    for (int64 chunk_index = 0; chunk_index < chunk_count; ++chunk_index) {
      const int64 patch_index_start = chunk_index * patches_per_chunk;
      const int64 patch_index_end =
          std::min(patch_index_start + patches_per_chunk, patch_count);
      for (int64 patch_index = patch_index_start; patch_index < patch_index_end;
           ++patch_index) {
        const int64 batch = patch_index / (output_height * output_width);
        const int64 out_y = (patch_index / output_width) % output_height;
        const int64 out_x = patch_index % output_width;
        const T1* input_batch_start =
            input_data + (batch * input_height * input_width * input_depth);
        const int in_y_origin = (out_y * stride) - filter_top_offset;
        const int in_x_origin = (out_x * stride) - filter_left_offset;
        const int patch_index_within_chunk = patch_index % patches_per_chunk;
        T1* im2col_patch_start =
            im2col_buffer + (patch_index_within_chunk * filter_value_count);
        for (int filter_y = 0; filter_y < filter_height; ++filter_y) {
          const int in_y = in_y_origin + filter_y;
          T1* im2col_row_start =
              im2col_patch_start + (filter_y * filter_width * input_depth);


          if ((in_y < 0) || (in_y >= input_height)) {


            memset(im2col_row_start, input_offset,
                   (filter_width * input_depth));
          } else {


            const int in_x_end = in_x_origin + filter_width;
            const int left_zero_count = std::max(0, 0 - in_x_origin);
            const int right_zero_count = std::max(0, in_x_end - input_width);
            const int center_copy_count =
                filter_width - (left_zero_count + right_zero_count);
            if (left_zero_count > 0) {
              T1* im2col_left_start = im2col_row_start;
              memset(im2col_left_start, input_offset,
                     (left_zero_count * input_depth));
            }
            if (center_copy_count > 0) {
              const T1* input_row_start =
                  input_batch_start + (in_y * input_width * input_depth) +
                  (std::max(0, in_x_origin) * input_depth);
              T1* im2col_center_start =
                  im2col_row_start + (left_zero_count * input_depth);
              memcpy(im2col_center_start, input_row_start,
                     (center_copy_count * input_depth));
            }
            if (right_zero_count > 0) {
              T1* im2col_right_start =
                  im2col_row_start +
                  ((left_zero_count + center_copy_count) * input_depth);
              memset(im2col_right_start, input_offset,
                     (right_zero_count * input_depth));
            }
          }
        }
      }


      const int how_many_patches = patch_index_end - patch_index_start;
      const bool transpose_a = false;
      const bool transpose_b = false;
      const bool transpose_c = false;
      const int m = how_many_patches;
      const int n = filter_count;
      const int k = filter_value_count;
      const int lda = filter_value_count;
      const int ldb = filter_count;
      const int ldc = filter_count;
      T3* chunk_output_data = output_data + (patch_index_start * filter_count);

      if (meta::IsSupportedAndEnabled() && std::is_same<T1, quint8>() &&
          std::is_same<T2, quint8>() && std::is_same<T3, qint32>() &&
          (output_offset == 0) && (output_mult == 1) && (output_shift == 0) &&
          (transpose_c == false) && (k <= 2048)) {
        meta::QuantizedGemm(context, transpose_a, transpose_b, im2col_buffer,
                            filter_data, chunk_output_data, m, n, k,
                            -input_offset, -filter_offset, lda, ldb, ldc);
      } else if (std::is_same<T1, quint8>() && std::is_same<T2, quint8>() &&
                 std::is_same<T3, qint32>() && (output_offset == 0) &&
                 (output_mult == 1) && (output_shift == 0)) {


        const uint8* im2col_data_as_uint8 = &(im2col_buffer->value);
        const uint8* filter_data_as_uint8 = &(filter_data->value);
        int32* output_data_as_int32 = &(chunk_output_data->value);


        static const gemmlowp::MapOrder ResultOrder =
            !transpose_c ? gemmlowp::MapOrder::RowMajor
                         : gemmlowp::MapOrder::ColMajor;
        static const gemmlowp::MapOrder LhsOrder =
            !transpose_a ? gemmlowp::MapOrder::RowMajor
                         : gemmlowp::MapOrder::ColMajor;
        static const gemmlowp::MapOrder RhsOrder =
            !transpose_b ? gemmlowp::MapOrder::RowMajor
                         : gemmlowp::MapOrder::ColMajor;
        gemmlowp::MatrixMap<const std::uint8_t, LhsOrder> lhs(
            im2col_data_as_uint8, m, k, lda);
        gemmlowp::MatrixMap<const std::uint8_t, RhsOrder> rhs(
            filter_data_as_uint8, k, n, ldb);
        gemmlowp::MatrixMap<std::int32_t, ResultOrder> result(
            output_data_as_int32, m, n, ldc);
        const std::tuple<> empty_pipeline = {};

        auto& worker_threads =
            *(context->device()->tensorflow_cpu_worker_threads());
        TensorflowGemmContext context(worker_threads.num_threads,
                                      worker_threads.workers);
        gemmlowp::GemmWithOutputPipeline<std::uint8_t, std::int32_t,
                                         gemmlowp::DefaultL8R8BitDepthParams>(
            &context, lhs, rhs, &result, -input_offset, -filter_offset,
            empty_pipeline);


        TF_ANNOTATE_MEMORY_IS_INITIALIZED(output_data_as_int32,
                                          m * n * sizeof(int32));
      } else {
        ReferenceGemm<T1, T2, T3>(
            transpose_a, transpose_b, transpose_c, m, n, k, im2col_buffer,
            input_offset, lda, filter_data, filter_offset, ldb,
            chunk_output_data, output_shift, output_offset, output_mult, ldc);
      }
    }
  }
