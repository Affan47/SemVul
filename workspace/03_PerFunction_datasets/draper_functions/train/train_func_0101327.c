qh_newridge(void) {
  ridgeT *ridge = NULL;
  void **freelistp;

  ridgeT_qh_memalloc_(sizeof(ridgeT), freelistp, ridge);
  memset ((char *)ridge, 0, sizeof(ridgeT));
  zinc_(Ztotridges);
  if (qh ridge_id == 0xFFFFFF) {
    fprintf(qh ferr, "\
qhull warning: more than %d ridges.  Id field overflows and two ridges\n\
may have the same identifier.  Otherwise output ok.\n", 0xFFFFFF);
  }
  ridge->id= qh ridge_id++;
  trace4((qh ferr, "qh_newridge: created ridge r%d\n", ridge->id));
  return (ridge);
}
