GetVFormatted(const char* format, va_list args) {
  Vector<char> str = Vector<char>::New(1024);
  int len = OS::VSNPrintF(str, format, args);
  if (len == -1) {
    DeleteArray(str.start());
    return format;
  }
  uint32_t hash = HashSequentialString(
      str.start(), len, HEAP->HashSeed());
  return AddOrDisposeString(str.start(), hash);
}
