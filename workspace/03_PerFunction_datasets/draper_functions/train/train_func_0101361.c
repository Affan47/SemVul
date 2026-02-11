do_calloc(size_t n, size_t elem_size) {

  const size_t size = n * elem_size;
  if (elem_size != 0 && size / elem_size != n) return NULL;

  void* result = do_malloc_no_errno_or_cpp_alloc(size);
  if (result == NULL) {
    errno = ENOMEM;
  } else {
    memset(result, 0, size);
  }
  return result;
}
