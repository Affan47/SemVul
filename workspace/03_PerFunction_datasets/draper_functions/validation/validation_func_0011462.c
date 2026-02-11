calloc (size_t nmemb, size_t size)
{


  size_t bytes = nmemb * size;

#define HALF_SIZE_T (((size_t) 1) << (8 * sizeof (size_t) / 2))
  if (__builtin_expect ((nmemb | size) >= HALF_SIZE_T, 0)
      && size != 0 && bytes / size != nmemb)
    return NULL;

  return malloc (bytes);
}
