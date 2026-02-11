GNUNET_xfree_ (void *ptr, const char *filename, int linenumber)
{
  GNUNET_assert_at (ptr != NULL, filename, linenumber);
#ifdef W32_MEM_LIMIT
  ptr = &((size_t *) ptr)[-1];
  mem_used -= *((size_t *) ptr);
#endif
  free (ptr);
}
