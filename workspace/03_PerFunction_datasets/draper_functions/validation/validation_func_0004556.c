open_temp_exec_file_dir (const char *dir)
{
  static const char suffix[] = "/ffiXXXXXX";
  size_t lendir = strlen (dir);
  char *tempname = __builtin_alloca (lendir + sizeof (suffix));

  if (!tempname)
    return -1;

  memcpy (tempname, dir, lendir);
  memcpy (tempname + lendir, suffix, sizeof (suffix));

  return open_temp_exec_file_name (tempname);
}
