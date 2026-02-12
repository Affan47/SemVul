find_handle_callback (char *filename, void *data, void *data2)
{
  lt_dlhandle  *phandle		= (lt_dlhandle *) data;
  int		notfound	= access (filename, R_OK);
  lt_dladvise   advise		= (lt_dladvise) data2;


  if (notfound)
    return 0;


  if (tryall_dlopen (phandle, filename, advise, 0) != 0)
    *phandle = 0;

  return 1;
}
