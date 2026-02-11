_GD_GenericTouch(struct _gd_raw_file* file)
{
  int fd;

  dtrace("%p", file);

  fd = open(file->name, O_RDWR | O_CREAT | O_TRUNC | O_BINARY, 0666);

  if (fd != -1)
    fd = close(fd);

  dreturn("%i", fd);
  return fd;
}
