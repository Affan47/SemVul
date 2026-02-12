static void fts3MatchinfoFunc(
  sqlite3_context *pContext,
  int nVal,
  sqlite3_value **apVal
){
  Fts3Cursor *pCsr;
  assert( nVal==1 || nVal==2 );
  if( SQLITE_OK==fts3FunctionArg(pContext, "matchinfo", apVal[0], &pCsr) ){
    const char *zArg = 0;
    if( nVal>1 ){
      zArg = (const char *)sqlite3_value_text(apVal[1]);
    }
    sqlite3Fts3Matchinfo(pContext, pCsr, zArg);
  }
}
