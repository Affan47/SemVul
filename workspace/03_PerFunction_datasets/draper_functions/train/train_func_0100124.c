check_dir(char *dir_name) {
#ifdef WIN32
  BOOL res;

  res = CreateDirectory(dir_name,NULL);
  if(res == 0) {
    return 0;
  } else {
    return 1;
  }
#else
  DIR *d;

  if (!(d=opendir(dir_name)) && (errno==ENOENT)) {
    mkdir(dir_name,0755);
    return 0;
  }
  return 1;
#endif
}
