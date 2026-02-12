static uint8_t* my_malloc(size_t size) {
  void* block = NULL;
  int res = 0;


#if defined(_WIN32)

  block = (void *)_aligned_malloc(size, 32);
#elif _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600

  res = posix_memalign(&block, 32, size);
#else
  block = malloc(size);
#endif

  if (block == NULL || res != 0) {
    printf("Error allocating memory!");
    return NULL;
  }

  return (uint8_t*)block;
}
