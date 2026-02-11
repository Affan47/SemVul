__vasprintf_chk (char **result_ptr, int flags, const char *format,
		 va_list args)
{


  const _IO_size_t init_string_size = 100;
  char *string;
  _IO_strfile sf;
  int ret;
  _IO_size_t needed;
  _IO_size_t allocated;


  string = (char *) malloc (init_string_size);
  if (string == NULL)
    return -1;
#ifdef _IO_MTSAFE_IO
  sf._sbf._f._lock = NULL;
#endif
  _IO_no_init (&sf._sbf._f, _IO_USER_LOCK, -1, NULL, NULL);
  _IO_JUMPS (&sf._sbf) = &_IO_str_jumps;
  _IO_str_init_static_internal (&sf, string, init_string_size, string);
  sf._sbf._f._flags &= ~_IO_USER_BUF;
  sf._s._allocate_buffer = (_IO_alloc_type) malloc;
  sf._s._free_buffer = (_IO_free_type) free;


  if (flags > 0)
    sf._sbf._f._flags2 |= _IO_FLAGS2_FORTIFY;

  ret = _IO_vfprintf (&sf._sbf._f, format, args);
  if (ret < 0)
    {
      free (sf._sbf._f._IO_buf_base);
      return ret;
    }


  needed = sf._sbf._f._IO_write_ptr - sf._sbf._f._IO_write_base + 1;
  allocated = sf._sbf._f._IO_write_end - sf._sbf._f._IO_write_base;
  if ((allocated >> 1) <= needed)
    *result_ptr = (char *) realloc (sf._sbf._f._IO_buf_base, needed);
  else
    {
      *result_ptr = (char *) malloc (needed);
      if (*result_ptr != NULL)
	{
	  memcpy (*result_ptr, sf._sbf._f._IO_buf_base, needed - 1);
	  free (sf._sbf._f._IO_buf_base);
	}
      else

	*result_ptr = (char *) realloc (sf._sbf._f._IO_buf_base, needed);
    }
  if (*result_ptr == NULL)
    *result_ptr = sf._sbf._f._IO_buf_base;
  (*result_ptr)[needed - 1] = '\0';
  return ret;
}
