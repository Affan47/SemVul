static int fts3MatchinfoLcsCb(
  Fts3Expr *pExpr,
  int iPhrase,
  void *pCtx
){
  LcsIterator *aIter = (LcsIterator *)pCtx;
  aIter[iPhrase].pExpr = pExpr;
  return SQLITE_OK;
}
