void DecodeImageV2Op::DecodeBMP(const uint8* input, const int row_size,
                                uint8* const output, const int width,
                                const int height, const int output_channels,
                                const int input_channels, bool top_down) {
  for (int i = 0; i < height; i++) {
    int src_pos;
    int dst_pos;

    for (int j = 0; j < width; j++) {
      if (!top_down) {
        src_pos = ((height - 1 - i) * row_size) + j * input_channels;
      } else {
        src_pos = i * row_size + j * input_channels;
      }

      dst_pos = (i * width + j) * output_channels;

      switch (input_channels) {
        case 1:
          output[dst_pos] = input[src_pos];


          if (output_channels == 3 || output_channels == 4) {
            output[dst_pos + 1] = input[src_pos];
            output[dst_pos + 2] = input[src_pos];
          }


          if (output_channels == 4) {
            output[dst_pos + 3] = UINT8_MAX;
          }
          break;
        case 3:

          output[dst_pos] = input[src_pos + 2];
          output[dst_pos + 1] = input[src_pos + 1];
          output[dst_pos + 2] = input[src_pos];


          if (output_channels == 4) {
            output[dst_pos + 3] = UINT8_MAX;
          }
          break;
        case 4:

          output[dst_pos] = input[src_pos + 2];
          output[dst_pos + 1] = input[src_pos + 1];
          output[dst_pos + 2] = input[src_pos];


          if (output_channels == 4) {
            output[dst_pos + 3] = input[src_pos + 3];
          }
          break;
        default:
          LOG(FATAL) << "Unexpected number of channels: " << input_channels;
          break;
      }
    }
  }
}
