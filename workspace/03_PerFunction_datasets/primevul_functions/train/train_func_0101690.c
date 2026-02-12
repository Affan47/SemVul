static int fts3ConnectMethod(
  sqlite3 *db,
  void *pAux,
  int argc,
  const char * const *argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  return fts3InitVtab(0, db, pAux, argc, argv, ppVtab, pzErr);
}
