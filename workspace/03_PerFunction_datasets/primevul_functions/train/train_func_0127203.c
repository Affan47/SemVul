static void resolveAlias(
  Parse *pParse,
  ExprList *pEList,
  int iCol,
  Expr *pExpr,
  const char *zType,
  int nSubquery
){
  Expr *pOrig;
  Expr *pDup;
  sqlite3 *db;

  assert( iCol>=0 && iCol<pEList->nExpr );
  pOrig = pEList->a[iCol].pExpr;
  assert( pOrig!=0 );
  db = pParse->db;
  pDup = sqlite3ExprDup(db, pOrig, 0);
  if( pDup!=0 ){
    if( zType[0]!='G' ) incrAggFunctionDepth(pDup, nSubquery);
    if( pExpr->op==TK_COLLATE ){
      pDup = sqlite3ExprAddCollateString(pParse, pDup, pExpr->u.zToken);
    }


    ExprSetProperty(pExpr, EP_Static);
    sqlite3ExprDelete(db, pExpr);
    memcpy(pExpr, pDup, sizeof(*pExpr));
    if( !ExprHasProperty(pExpr, EP_IntValue) && pExpr->u.zToken!=0 ){
      assert( (pExpr->flags & (EP_Reduced|EP_TokenOnly))==0 );
      pExpr->u.zToken = sqlite3DbStrDup(db, pExpr->u.zToken);
      pExpr->flags |= EP_MemToken;
    }
    if( ExprHasProperty(pExpr, EP_WinFunc) ){
      if( pExpr->y.pWin!=0 ){
        pExpr->y.pWin->pOwner = pExpr;
      }else{
        assert( db->mallocFailed );
      }
    }
    sqlite3DbFree(db, pDup);
  }
  ExprSetProperty(pExpr, EP_Alias);
}
