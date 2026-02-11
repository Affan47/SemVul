btAlignedAllocDefault(size_t size, int alignment)
{
  void *ret;
  char *real;
  unsigned long offset;

  real = (char *)sAllocFunc(size + sizeof(void *) + (alignment-1));
  if (real) {
    offset = (alignment - (unsigned long)(real + sizeof(void *))) & (alignment-1);
    ret = (void *)((real + sizeof(void *)) + offset);
    *((void **)(ret)-1) = (void *)(real);
  } else {
    ret = (void *)(real);
  }
  return (ret);
}
