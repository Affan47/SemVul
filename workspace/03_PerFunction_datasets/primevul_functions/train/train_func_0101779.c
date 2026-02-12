static int fts3UpdateMethod(
  sqlite3_vtab *pVtab,
  int nArg,
  sqlite3_value **apVal,
  sqlite_int64 *pRowid
){
  return sqlite3Fts3UpdateMethod(pVtab, nArg, apVal, pRowid);
}
