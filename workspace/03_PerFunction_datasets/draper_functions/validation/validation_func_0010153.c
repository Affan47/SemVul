scm_calloc (size_t sz)
{
  void * ptr;


  SCM_SYSCALL (ptr = calloc (sz, 1));
  if (ptr)
    return ptr;

  ptr = scm_realloc (NULL, sz);
  memset (ptr, 0x0, sz);
  return ptr;
}
