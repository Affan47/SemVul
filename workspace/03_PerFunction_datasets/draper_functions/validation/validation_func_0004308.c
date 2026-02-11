d(int dir, const char* subdir,
      unsigned uid, unsigned gid, unsigned mode)
{
  xchdir(dir);
  if (path_mkdirs(subdir, 0700) == -1 && errno != EEXIST)
    diefsys(1, "{Could not create directory }s", subdir);
  if ((dir = open(subdir, O_RDONLY)) == -1)
    diefsys(1, "{Could not open created directory }s", subdir);
  setmodes(subdir, uid, gid, mode);
  return dir;
}
