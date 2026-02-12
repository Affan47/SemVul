static int countOfViewOptimization(Parse *pParse, Select *p){
  Select *pSub, *pPrior;
  Expr *pExpr;
  Expr *pCount;
  sqlite3 *db;
  if( (p->selFlags & SF_Aggregate)==0 ) return 0;
  if( p->pEList->nExpr!=1 ) return 0;
  if( p->pWhere ) return 0;
  if( p->pGroupBy ) return 0;
  pExpr = p->pEList->a[0].pExpr;
  if( pExpr->op!=TK_AGG_FUNCTION ) return 0;
  if( sqlite3_stricmp(pExpr->u.zToken,"count") ) return 0;
  if( pExpr->x.pList!=0 ) return 0;
  if( p->pSrc->nSrc!=1 ) return 0;
  pSub = p->pSrc->a[0].pSelect;
  if( pSub==0 ) return 0;
  if( pSub->pPrior==0 ) return 0;
  do{
    if( pSub->op!=TK_ALL && pSub->pPrior ) return 0;
    if( pSub->pWhere ) return 0;
    if( pSub->pLimit ) return 0;
    if( pSub->selFlags & SF_Aggregate ) return 0;
    pSub = pSub->pPrior;
  }while( pSub );


  db = pParse->db;
  pCount = pExpr;
  pExpr = 0;
  pSub = p->pSrc->a[0].pSelect;
  p->pSrc->a[0].pSelect = 0;
  sqlite3SrcListDelete(db, p->pSrc);
  p->pSrc = sqlite3DbMallocZero(pParse->db, sizeof(*p->pSrc));
  while( pSub ){
    Expr *pTerm;
    pPrior = pSub->pPrior;
    pSub->pPrior = 0;
    pSub->pNext = 0;
    pSub->selFlags |= SF_Aggregate;
    pSub->selFlags &= ~SF_Compound;
    pSub->nSelectRow = 0;
    sqlite3ExprListDelete(db, pSub->pEList);
    pTerm = pPrior ? sqlite3ExprDup(db, pCount, 0) : pCount;
    pSub->pEList = sqlite3ExprListAppend(pParse, 0, pTerm);
    pTerm = sqlite3PExpr(pParse, TK_SELECT, 0, 0);
    sqlite3PExprAddSelect(pParse, pTerm, pSub);
    if( pExpr==0 ){
      pExpr = pTerm;
    }else{
      pExpr = sqlite3PExpr(pParse, TK_PLUS, pTerm, pExpr);
    }
    pSub = pPrior;
  }
  p->pEList->a[0].pExpr = pExpr;
  p->selFlags &= ~SF_Aggregate;

#if SELECTTRACE_ENABLED
  if( sqlite3SelectTrace & 0x400 ){
    SELECTTRACE(0x400,pParse,p,("After count-of-view optimization:\n"));
    sqlite3TreeViewSelect(0, p, 0);
  }
#endif
  return 1;
}
