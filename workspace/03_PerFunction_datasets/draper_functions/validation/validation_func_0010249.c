_IO_old_fopencookie (cookie, mode, io_functions)
     void *cookie;
     const char *mode;
     _IO_cookie_io_functions_t io_functions;
{
  _IO_FILE *ret;

  ret = _IO_fopencookie (cookie, mode, io_functions);
  if (ret != NULL)
    _IO_JUMPS ((struct _IO_FILE_plus *) ret) = &_IO_old_cookie_jumps;

  return ret;
}
