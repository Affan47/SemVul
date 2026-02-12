static void fts3OffsetsFunc(
  sqlite3_context *pContext,
  int nVal,
  sqlite3_value **apVal
){
  Fts3Cursor *pCsr;

  UNUSED_PARAMETER(nVal);

  assert( nVal==1 );
  if( fts3FunctionArg(pContext, "offsets", apVal[0], &pCsr) ) return;
  assert( pCsr );
  if( SQLITE_OK==fts3CursorSeek(pContext, pCsr) ){
    sqlite3Fts3Offsets(pContext, pCsr);
  }
}
