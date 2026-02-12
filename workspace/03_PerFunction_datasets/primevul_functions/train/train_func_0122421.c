static Select *isCandidateForInOpt(Expr *pX){
  Select *p;
  SrcList *pSrc;
  ExprList *pEList;
  Table *pTab;
  int i;
  if( !ExprHasProperty(pX, EP_xIsSelect) ) return 0;
  if( ExprHasProperty(pX, EP_VarSelect)  ) return 0;
  p = pX->x.pSelect;
  if( p->pPrior ) return 0;
  if( p->selFlags & (SF_Distinct|SF_Aggregate) ){
    testcase( (p->selFlags & (SF_Distinct|SF_Aggregate))==SF_Distinct );
    testcase( (p->selFlags & (SF_Distinct|SF_Aggregate))==SF_Aggregate );
    return 0;
  }
  assert( p->pGroupBy==0 );
  if( p->pLimit ) return 0;
  if( p->pWhere ) return 0;
  pSrc = p->pSrc;
  assert( pSrc!=0 );
  if( pSrc->nSrc!=1 ) return 0;
  if( pSrc->a[0].pSelect ) return 0;
  pTab = pSrc->a[0].pTab;
  assert( pTab!=0 );
  assert( pTab->pSelect==0 );
  if( IsVirtual(pTab) ) return 0;
  pEList = p->pEList;
  assert( pEList!=0 );

  for(i=0; i<pEList->nExpr; i++){
    Expr *pRes = pEList->a[i].pExpr;
    if( pRes->op!=TK_COLUMN ) return 0;
    assert( pRes->iTable==pSrc->a[0].iCursor );
  }
  return p;
}
