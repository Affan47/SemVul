getNextEntry() {
  GDirEntry *e;

#if defined(_WIN32)
  if (hnd != INVALID_HANDLE_VALUE) {
    e = new GDirEntry(path->getCString(), ffd.cFileName, doStat);
    if (!FindNextFile(hnd, &ffd)) {
      FindClose(hnd);
      hnd = INVALID_HANDLE_VALUE;
    }
  } else {
    e = NULL;
  }
#elif defined(ACORN)
#elif defined(MACOS)
#elif defined(VMS)
  struct dirent *ent;
  e = NULL;
  if (dir) {
    if (needParent) {
      e = new GDirEntry(path->getCString(), "-", doStat);
      needParent = gFalse;
      return e;
    }
    ent = readdir(dir);
    if (ent) {
      e = new GDirEntry(path->getCString(), ent->d_name, doStat);
    }
  }
#else
  struct dirent *ent;
  e = NULL;
  if (dir) {
    do {
      ent = readdir(dir);
    }
    while (ent && (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")));
    if (ent) {
      e = new GDirEntry(path->getCString(), ent->d_name, doStat);
    }
  }
#endif

  return e;
}
