static int zipfileFindFunction(
  sqlite3_vtab *pVtab,
  int nArg,
  const char *zName,
  void (**pxFunc)(sqlite3_context*,int,sqlite3_value**),
  void **ppArg
){
  if( sqlite3_stricmp("zipfile_cds", zName)==0 ){
    *pxFunc = zipfileFunctionCds;
    *ppArg = (void*)pVtab;
    return 1;
  }
  return 0;
}
