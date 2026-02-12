void sqlite3ExprListSetSpan(
  Parse *pParse,
  ExprList *pList,
  const char *zStart,
  const char *zEnd
){
  sqlite3 *db = pParse->db;
  assert( pList!=0 || db->mallocFailed!=0 );
  if( pList ){
    struct ExprList_item *pItem = &pList->a[pList->nExpr-1];
    assert( pList->nExpr>0 );
    sqlite3DbFree(db, pItem->zSpan);
    pItem->zSpan = sqlite3DbSpanDup(db, zStart, zEnd);
  }
}
