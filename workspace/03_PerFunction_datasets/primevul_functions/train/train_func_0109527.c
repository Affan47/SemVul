static int whereRangeVectorLen(
  Parse *pParse,
  int iCur,
  Index *pIdx,
  int nEq,
  WhereTerm *pTerm
){
  int nCmp = sqlite3ExprVectorSize(pTerm->pExpr->pLeft);
  int i;

  nCmp = MIN(nCmp, (pIdx->nColumn - nEq));
  for(i=1; i<nCmp; i++){


    char aff;
    char idxaff = 0;
    CollSeq *pColl;
    Expr *pLhs, *pRhs;

    assert( ExprUseXList(pTerm->pExpr->pLeft) );
    pLhs = pTerm->pExpr->pLeft->x.pList->a[i].pExpr;
    pRhs = pTerm->pExpr->pRight;
    if( ExprUseXSelect(pRhs) ){
      pRhs = pRhs->x.pSelect->pEList->a[i].pExpr;
    }else{
      pRhs = pRhs->x.pList->a[i].pExpr;
    }


    if( pLhs->op!=TK_COLUMN
     || pLhs->iTable!=iCur
     || pLhs->iColumn!=pIdx->aiColumn[i+nEq]
     || pIdx->aSortOrder[i+nEq]!=pIdx->aSortOrder[nEq]
    ){
      break;
    }

    testcase( pLhs->iColumn==XN_ROWID );
    aff = sqlite3CompareAffinity(pRhs, sqlite3ExprAffinity(pLhs));
    idxaff = sqlite3TableColumnAffinity(pIdx->pTable, pLhs->iColumn);
    if( aff!=idxaff ) break;

    pColl = sqlite3BinaryCompareCollSeq(pParse, pLhs, pRhs);
    if( pColl==0 ) break;
    if( sqlite3StrICmp(pColl->zName, pIdx->azColl[i+nEq]) ) break;
  }
  return i;
}
