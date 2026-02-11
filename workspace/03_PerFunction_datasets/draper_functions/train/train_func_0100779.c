C_i_fifo_p(C_word name)
{
  struct stat buf;
  int res;

  res = stat(C_c_string(name), &buf);

  if(res != 0) {
#ifdef __CYGWIN__
    return C_SCHEME_FALSE;
#else
    if(errno == ENOENT) return C_fix(0);
    else return C_fix(res);
#endif
  }

  if((buf.st_mode & S_IFMT) == S_IFIFO) return C_SCHEME_TRUE;
  else return C_SCHEME_FALSE;
}
