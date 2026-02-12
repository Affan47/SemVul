inline void Resize(int dimensions_count) {
    if (size_ > kMaxSmallSize) {
#ifdef TF_LITE_STATIC_MEMORY
      TFLITE_CHECK(false && "No shape resizing supported on this platform");
#else
      delete[] dims_pointer_;
#endif
    }
    size_ = dimensions_count;
    if (dimensions_count > kMaxSmallSize) {
#ifdef TF_LITE_STATIC_MEMORY
      TFLITE_CHECK(false && "No shape resizing supported on this platform");
#else
      dims_pointer_ = new int32_t[dimensions_count];
#endif
    }
  }
