cmalloc (size_t nmemb, size_t size)
{

  if (nmemb >= ~(size_t) 0 / size)
    return NULL;

  return xmalloc (nmemb * size);
}
