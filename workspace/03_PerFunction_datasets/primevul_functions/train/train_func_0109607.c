static int isDistinctRedundant(
  Parse *pParse,
  SrcList *pTabList,
  WhereClause *pWC,
  ExprList *pDistinct
){
  Table *pTab;
  Index *pIdx;
  int i;
  int iBase;


  if( pTabList->nSrc!=1 ) return 0;
  iBase = pTabList->a[0].iCursor;
  pTab = pTabList->a[0].pTab;


  for(i=0; i<pDistinct->nExpr; i++){
    Expr *p = sqlite3ExprSkipCollateAndLikely(pDistinct->a[i].pExpr);
    if( NEVER(p==0) ) continue;
    if( p->op!=TK_COLUMN && p->op!=TK_AGG_COLUMN ) continue;
    if( p->iTable==iBase && p->iColumn<0 ) return 1;
  }


  for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
    if( !IsUniqueIndex(pIdx) ) continue;
    if( pIdx->pPartIdxWhere ) continue;
    for(i=0; i<pIdx->nKeyCol; i++){
      if( 0==sqlite3WhereFindTerm(pWC, iBase, i, ~(Bitmask)0, WO_EQ, pIdx) ){
        if( findIndexCol(pParse, pDistinct, iBase, pIdx, i)<0 ) break;
        if( indexColumnNotNull(pIdx, i)==0 ) break;
      }
    }
    if( i==pIdx->nKeyCol ){

      return 1;
    }
  }

  return 0;
}
