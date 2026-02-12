static int fts3ExprIterate2(
  Fts3Expr *pExpr,
  int *piPhrase,
  int (*x)(Fts3Expr*,int,void*),
  void *pCtx
){
  int rc;
  int eType = pExpr->eType;

  if( eType!=FTSQUERY_PHRASE ){
    assert( pExpr->pLeft && pExpr->pRight );
    rc = fts3ExprIterate2(pExpr->pLeft, piPhrase, x, pCtx);
    if( rc==SQLITE_OK && eType!=FTSQUERY_NOT ){
      rc = fts3ExprIterate2(pExpr->pRight, piPhrase, x, pCtx);
    }
  }else{
    rc = x(pExpr, *piPhrase, pCtx);
    (*piPhrase)++;
  }
  return rc;
}
