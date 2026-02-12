static size_t BufferBytesForLength(int length) {
    return (length + 1) * sizeof(TypedValue) / 2;
  }
