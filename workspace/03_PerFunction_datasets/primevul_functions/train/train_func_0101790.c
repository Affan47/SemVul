static int fts3CreateMethod(
  sqlite3 *db,
  void *pAux,
  int argc,
  const char * const *argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  return fts3InitVtab(1, db, pAux, argc, argv, ppVtab, pzErr);
}
