void DecodeGifV2(OpKernelContext* context, StringPiece input) {

    OP_REQUIRES(context, channels_ == 0 || channels_ == 3,
                errors::InvalidArgument("channels must be 0 or 3 for GIF, got ",
                                        channels_));

    if (op_type_ == "DecodeBmp") {


      OP_REQUIRES(context, false,
                  errors::InvalidArgument(
                      "Trying to decode GIF format using DecodeBmp op. Use "
                      "`decode_gif` or `decode_image` instead."));
    } else if (op_type_ == "DecodeAndCropJpeg") {
      OP_REQUIRES(context, false,
                  errors::InvalidArgument(
                      "DecodeAndCropJpeg operation can run on JPEG only, but "
                      "detected GIF."));
    }


    Tensor* output = nullptr;
    int buffer_size = 0;
    string error_string;
    uint8* buffer = gif::Decode(
        input.data(), input.size(),
        [&](int num_frames, int width, int height, int channels) -> uint8* {
          buffer_size = num_frames * height * width * channels;

          Status status;


          if (op_type_ == "DecodePng" || op_type_ == "DecodeJpeg") {
            if (num_frames == 1) {
              status = context->allocate_output(
                  0, TensorShape({height, width, channels}), &output);
            } else {
              status = errors::InvalidArgument(
                  "Got ", num_frames, " frames, but animated gifs ",
                  "can only be decoded by tf.io.decode_gif or ",
                  "tf.io.decode_image");
            }
          } else if (op_type_ == "DecodeGif" ||
                     (op_type_ == "DecodeImage" && expand_animations_)) {
            status = context->allocate_output(
                0, TensorShape({num_frames, height, width, channels}), &output);
          } else if (op_type_ == "DecodeImage" && !expand_animations_) {
            status = context->allocate_output(
                0, TensorShape({height, width, channels}), &output);
          } else {
            status = errors::InvalidArgument("Bad op type ", op_type_);
          }
          if (!status.ok()) {
            VLOG(1) << status;
            context->SetStatus(status);
            return nullptr;
          }

          if (data_type_ == DataType::DT_UINT8) {
            return output->flat<uint8>().data();
          } else {
            return new uint8[buffer_size];
          }
        },
        &error_string, expand_animations_);

    OP_REQUIRES(context, buffer,
                errors::InvalidArgument("Invalid GIF data (size ", input.size(),
                                        "), ", error_string));


    if (data_type_ == DataType::DT_UINT8) {
      return;
    }

    std::unique_ptr<uint8[]> buffer_unique_ptr(buffer);


    TTypes<uint8>::UnalignedConstFlat buffer_view(buffer, buffer_size);
    const auto& device = context->eigen_device<Eigen::ThreadPoolDevice>();
    if (data_type_ == DataType::DT_UINT16) {
      uint16 scale = floor((std::numeric_limits<uint16>::max() + 1) /
                           (std::numeric_limits<uint8>::max() + 1));

      output->flat<uint16>().device(device) =
          buffer_view.cast<uint16>() * scale;
    } else if (data_type_ == DataType::DT_FLOAT) {
      float scale = 1. / std::numeric_limits<uint8>::max();

      output->flat<float>().device(device) = buffer_view.cast<float>() * scale;
    }
  }
