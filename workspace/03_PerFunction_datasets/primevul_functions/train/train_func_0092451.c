void Compute(OpKernelContext* context) override {
    const Tensor& contents = context->input(0);
    OP_REQUIRES(context, TensorShapeUtils::IsScalar(contents.shape()),
                errors::InvalidArgument("contents must be scalar, got shape ",
                                        contents.shape().DebugString()));


    const StringPiece input = contents.scalar<string>()();

    OP_REQUIRES(context, (32 <= input.size()),
                errors::InvalidArgument("Incomplete bmp content, requires at "
                                        "least 32 bytes to find the header "
                                        "size, width, height, and bpp, got ",
                                        input.size(), " bytes"));

    const uint8* img_bytes = reinterpret_cast<const uint8*>(input.data());
    int32 header_size_ = internal::SubtleMustCopy(
        *(reinterpret_cast<const int32*>(img_bytes + 10)));
    const int32 header_size = ByteSwapInt32ForBigEndian(header_size_);
    int32 width_ = internal::SubtleMustCopy(
        *(reinterpret_cast<const int32*>(img_bytes + 18)));
    const int32 width = ByteSwapInt32ForBigEndian(width_);
    int32 height_ = internal::SubtleMustCopy(
        *(reinterpret_cast<const int32*>(img_bytes + 22)));
    const int32 height = ByteSwapInt32ForBigEndian(height_);
    int32 bpp_ = internal::SubtleMustCopy(
        *(reinterpret_cast<const int32*>(img_bytes + 28)));
    const int32 bpp = ByteSwapInt32ForBigEndian(bpp_);

    if (channels_) {
      OP_REQUIRES(context, (channels_ == bpp / 8),
                  errors::InvalidArgument(
                      "channels attribute ", channels_,
                      " does not match bits per pixel from file ", bpp / 8));
    } else {
      channels_ = bpp / 8;
    }


    OP_REQUIRES(context, (channels_ == 1 || channels_ == 3 || channels_ == 4),
                errors::InvalidArgument(
                    "Number of channels must be 1, 3 or 4, was ", channels_));

    OP_REQUIRES(context, width > 0 && header_size >= 0,
                errors::InvalidArgument("Width must be positive"));
    OP_REQUIRES(context, header_size >= 0,
                errors::InvalidArgument("header size must be nonnegative"));


    OP_REQUIRES(
        context,
        (static_cast<int64>(width) * std::abs(static_cast<int64>(height))) <
            static_cast<int64>(std::numeric_limits<int32_t>::max() / 8),
        errors::InvalidArgument(
            "Total possible pixel bytes must be less than 2^30"));

    const int32 abs_height = abs(height);


    const int row_size = (8 * channels_ * width + 31) / 32 * 4;

    const int64 last_pixel_offset = static_cast<int64>(header_size) +
                                    (abs_height - 1) * row_size +
                                    (width - 1) * channels_;


    const int64 expected_file_size = last_pixel_offset + channels_;

    OP_REQUIRES(
        context, (expected_file_size <= input.size()),
        errors::InvalidArgument("Incomplete bmp content, requires at least ",
                                expected_file_size, " bytes, got ",
                                input.size(), " bytes"));


    bool top_down = (height < 0);


    Tensor* output = nullptr;
    OP_REQUIRES_OK(
        context, context->allocate_output(
                     0, TensorShape({abs_height, width, channels_}), &output));

    const uint8* bmp_pixels = &img_bytes[header_size];

    Decode(bmp_pixels, row_size, output->flat<uint8>().data(), width,
           abs_height, channels_, top_down);
  }
