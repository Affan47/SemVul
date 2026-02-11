plInBuildTree(void)
{
  static int inited = 0;
  static int inBuildTree = 0;

  if (inited == 0) {
    char currdir[256];


#if defined(WIN32) && !defined(__BORLANDC__)
#define getcwd _getcwd
#endif

    if (getcwd(currdir, 256) == NULL) {
      pldebug("plInBuildTree():", "Not enough buffer space");
    } else if (strncmp(BUILD_DIR, currdir, strlen(BUILD_DIR)) == 0)
      inBuildTree = 1;
    inited = 1;
  }
  return inBuildTree;
}
