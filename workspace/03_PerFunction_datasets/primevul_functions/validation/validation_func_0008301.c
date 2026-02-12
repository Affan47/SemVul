int blosc_getitem(const void* src, int start, int nitems, void* dest) {
  uint8_t* _src = (uint8_t*)(src);
  blosc2_context context;
  int result;

  uint8_t version = _src[0];
  if (version > BLOSC_VERSION_FORMAT) {

    return -1;
  }


  memset(&context, 0, sizeof(blosc2_context));
  context.src = src;
  context.dest = dest;
  context.typesize = (uint8_t)_src[3];
  context.blocksize = sw32_(_src + 8);
  context.header_flags = *(_src + 2);
  context.filter_flags = get_filter_flags(context.header_flags, context.typesize);
  context.schunk = g_schunk;
  context.nthreads = 1;
  context.serial_context = create_thread_context(&context, 0);


  result = _blosc_getitem(&context, src, INT32_MAX, start, nitems, dest);


  free_thread_context(context.serial_context);
  return result;
}
