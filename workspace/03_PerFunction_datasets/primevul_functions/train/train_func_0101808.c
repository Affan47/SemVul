static int fts3ContentColumns(
  sqlite3 *db,
  const char *zDb,
  const char *zTbl,
  const char ***pazCol,
  int *pnCol,
  int *pnStr
){
  int rc = SQLITE_OK;
  char *zSql;
  sqlite3_stmt *pStmt = 0;

  zSql = sqlite3_mprintf("SELECT * FROM %Q.%Q", zDb, zTbl);
  if( !zSql ){
    rc = SQLITE_NOMEM;
  }else{
    rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
  }
  sqlite3_free(zSql);

  if( rc==SQLITE_OK ){
    const char **azCol;
    int nStr = 0;
    int nCol;
    int i;


    nCol = sqlite3_column_count(pStmt);
    for(i=0; i<nCol; i++){
      const char *zCol = sqlite3_column_name(pStmt, i);
      nStr += (int)strlen(zCol) + 1;
    }


    azCol = (const char **)sqlite3_malloc(sizeof(char *) * nCol + nStr);
    if( azCol==0 ){
      rc = SQLITE_NOMEM;
    }else{
      char *p = (char *)&azCol[nCol];
      for(i=0; i<nCol; i++){
        const char *zCol = sqlite3_column_name(pStmt, i);
        int n = (int)strlen(zCol)+1;
        memcpy(p, zCol, n);
        azCol[i] = p;
        p += n;
      }
    }
    sqlite3_finalize(pStmt);


    *pnCol = nCol;
    *pnStr = nStr;
    *pazCol = azCol;
  }

  return rc;
}
