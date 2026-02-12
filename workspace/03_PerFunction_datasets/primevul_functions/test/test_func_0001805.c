open_namespace_fd_if_needed (const char *path,
                             const char *other_path) {
  struct stat s, other_s;

  if (stat (path, &s) != 0)
    return -1;

  if (stat (other_path, &other_s) != 0)
    return -1;


  if (s.st_ino != other_s.st_ino)
    return open (path, O_RDONLY|O_CLOEXEC);

  return -1;
}
