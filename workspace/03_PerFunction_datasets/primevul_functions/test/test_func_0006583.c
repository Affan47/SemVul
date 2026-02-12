get_path_max (void)
{
# ifdef PATH_MAX
  long int path_max = PATH_MAX;
# else


  int err = errno;
  long int path_max = __pathconf ("/", _PC_PATH_MAX);
  __set_errno (err);
# endif
  return path_max < 0 ? 1024 : path_max <= IDX_MAX ? path_max : IDX_MAX;
}
