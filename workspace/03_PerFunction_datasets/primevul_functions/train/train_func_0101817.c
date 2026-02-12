static int fts3ExprLoadDoclists(
  Fts3Cursor *pCsr,
  int *pnPhrase,
  int *pnToken
){
  int rc;
  LoadDoclistCtx sCtx = {0,0,0};
  sCtx.pCsr = pCsr;
  rc = fts3ExprIterate(pCsr->pExpr, fts3ExprLoadDoclistsCb, (void *)&sCtx);
  if( pnPhrase ) *pnPhrase = sCtx.nPhrase;
  if( pnToken ) *pnToken = sCtx.nToken;
  return rc;
}
