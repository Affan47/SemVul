createDir(char *z) {
  DIR *tdir;
  tdir=opendir(z);
  if (tdir)
    closedir(tdir);
  else
    if (mkdir(z,0755)) {
      cerr << _("[eboard] ** failed to create directory ") << z << endl;
      return -1;
    }
  return 0;
}
