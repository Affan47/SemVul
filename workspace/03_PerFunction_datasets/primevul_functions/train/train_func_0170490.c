static void* H2Realloc(void* ptr, size_t size, void* user_data) {
    Http2Session* session = static_cast<Http2Session*>(user_data);
    size_t previous_size = 0;
    char* original_ptr = nullptr;


    if (size > 0) size += sizeof(size_t);

    if (ptr != nullptr) {

      original_ptr = static_cast<char*>(ptr) - sizeof(size_t);
      previous_size = *reinterpret_cast<size_t*>(original_ptr);

      if (previous_size == 0) {

        char* ret = UncheckedRealloc(original_ptr, size);
        if (ret != nullptr)
          ret += sizeof(size_t);
        return ret;
      }
    }
    CHECK_GE(session->current_nghttp2_memory_, previous_size);


    char* mem = UncheckedRealloc(original_ptr, size);

    if (mem != nullptr) {

      session->current_nghttp2_memory_ += size - previous_size;
      *reinterpret_cast<size_t*>(mem) = size;
      mem += sizeof(size_t);
    } else if (size == 0) {
      session->current_nghttp2_memory_ -= previous_size;
    }

    return mem;
  }
