void operator()(OpKernelContext* context, const T1* input_data,
                  int input_batches, int input_height, int input_width,
                  int input_depth, int input_offset, const T2* filter_data,
                  int filter_height, int filter_width, int filter_count,
                  int filter_offset, int stride, Padding padding,
                  T3* output_data, int output_height, int output_width,
                  int output_shift, int output_offset, int output_mult) {


    const int32 highest = static_cast<int32>(Eigen::NumTraits<T3>::highest());
    const int32 lowest = static_cast<int32>(Eigen::NumTraits<T3>::lowest());


    const int32 rounding = (output_shift < 1) ? 0 : (1 << (output_shift - 1));


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


    for (int batch = 0; batch < input_batches; ++batch) {


      for (int out_y = 0; out_y < output_height; ++out_y) {
        for (int out_x = 0; out_x < output_width; ++out_x) {

          for (int out_channel = 0; out_channel < filter_count; ++out_channel) {


            const int in_x_origin = (out_x * stride) - filter_left_offset;
            const int in_y_origin = (out_y * stride) - filter_top_offset;
            int32 total = 0;
            for (int filter_y = 0; filter_y < filter_height; ++filter_y) {
              for (int filter_x = 0; filter_x < filter_width; ++filter_x) {
                for (int in_channel = 0; in_channel < input_depth;
                     ++in_channel) {
                  const int in_x = in_x_origin + filter_x;
                  const int in_y = in_y_origin + filter_y;
                  int32 input_value;


                  if ((in_x >= 0) && (in_x < input_width) && (in_y >= 0) &&
                      (in_y < input_height)) {
                    const T1 input_source_value =
                        input_data[(batch * input_height * input_width *
                                    input_depth) +
                                   (in_y * input_width * input_depth) +
                                   (in_x * input_depth) + in_channel];


                    input_value =
                        static_cast<int32>(input_source_value) - input_offset;
                  } else {
                    input_value = 0;
                  }
                  const T2 filter_source_value =
                      filter_data[(filter_y * filter_width * input_depth *
                                   filter_count) +
                                  (filter_x * input_depth * filter_count) +
                                  (in_channel * filter_count) + out_channel];

                  const int32 filter_value =
                      static_cast<int32>(filter_source_value) - filter_offset;
                  total += (input_value * filter_value);
                }
              }
            }


            const int32_t output =
                ((((total + output_offset) * output_mult) + rounding) >>
                 output_shift);


            const int32 top_clamped_output = std::min(output, highest);
            const int32 clamped_output = std::max(top_clamped_output, lowest);
            output_data[(batch * output_height * output_width * filter_count) +
                        (out_y * output_width * filter_count) +
                        (out_x * filter_count) + out_channel] = clamped_output;
          }
        }
      }
    }
  }
