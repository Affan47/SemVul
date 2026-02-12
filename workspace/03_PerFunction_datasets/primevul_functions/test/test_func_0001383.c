void DecodeJpegV2(OpKernelContext* context, StringPiece input) {
    OP_REQUIRES(context, channels_ == 0 || channels_ == 1 || channels_ == 3,
                errors::InvalidArgument("JPEG does not support 4 channels"));


    jpeg::UncompressFlags flags = flags_;
    flags.components = channels_;

    if (op_type_ == "DecodeAndCropJpeg") {
      flags.crop = true;

      const Tensor& crop_window = context->input(1);
      OP_REQUIRES(context, crop_window.dims() == 1,
                  errors::InvalidArgument("crop_window must be 1-D, got shape ",
                                          crop_window.shape().DebugString()));
      OP_REQUIRES(context, crop_window.dim_size(0) == 4,
                  errors::InvalidArgument("crop_size must have four elements ",
                                          crop_window.shape().DebugString()));
      auto crop_window_vec = crop_window.vec<int32>();
      flags.crop_y = crop_window_vec(0);
      flags.crop_x = crop_window_vec(1);
      flags.crop_height = crop_window_vec(2);
      flags.crop_width = crop_window_vec(3);
    } else if (op_type_ == "DecodeBmp") {


      OP_REQUIRES(context, false,
                  errors::InvalidArgument(
                      "Trying to decode JPEG format using DecodeBmp op. Use "
                      "`decode_jpeg` or `decode_image` instead."));
    }


    Tensor* output = nullptr;
    int buffer_size = 0;


    uint8* buffer = jpeg::Uncompress(
        input.data(), input.size(), flags, nullptr ,
        [&](int width, int height, int channels) -> uint8* {
          buffer_size = height * width * channels;
          Status status;


          if (op_type_ == "DecodeGif") {
            status = context->allocate_output(
                0, TensorShape({1, height, width, channels}), &output);
          } else {
            status = context->allocate_output(
                0, TensorShape({height, width, channels}), &output);
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
        });

    OP_REQUIRES(
        context, buffer,
        errors::InvalidArgument(
            "jpeg::Uncompress failed. Invalid JPEG data or crop window."));


    if (data_type_ == DataType::DT_UINT8) {
      return;
    }

    std::unique_ptr<uint8[]> buffer_unique_ptr(buffer);


    const auto& device = context->eigen_device<Eigen::ThreadPoolDevice>();
    TTypes<uint8>::UnalignedConstFlat buffer_view(buffer, buffer_size);
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
