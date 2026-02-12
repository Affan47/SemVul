int TfLiteFloatArrayGetSizeInBytes(int size) {
  static TfLiteFloatArray dummy;

  int computed_size = sizeof(dummy) + sizeof(dummy.data[0]) * size;
#if defined(_MSC_VER)

  computed_size -= sizeof(dummy.data[0]);
#endif
  return computed_size;
}
