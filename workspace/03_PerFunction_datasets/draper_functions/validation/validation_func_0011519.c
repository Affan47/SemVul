checkdir(const char *path)
{
  struct stat dirstat;
  if(stat(path,&dirstat)==0) {
    if(S_ISDIR(dirstat.st_mode)) return 1;
    else return 0;
  }
  else if(errno == error_noent) return 0;
  return -1;
}
