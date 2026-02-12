static int fts3ExprIterate(
  Fts3Expr *pExpr,
  int (*x)(Fts3Expr*,int,void*),
  void *pCtx
){
  int iPhrase = 0;
  return fts3ExprIterate2(pExpr, &iPhrase, x, pCtx);
}
