static int fts3ExprGlobalHitsCb(
  Fts3Expr *pExpr,
  int iPhrase,
  void *pCtx
){
  MatchInfo *p = (MatchInfo *)pCtx;
  return sqlite3Fts3EvalPhraseStats(
      p->pCursor, pExpr, &p->aMatchinfo[3*iPhrase*p->nCol]
  );
}
