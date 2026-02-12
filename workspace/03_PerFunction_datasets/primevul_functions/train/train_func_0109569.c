static void whereLoopOutputAdjust(
  WhereClause *pWC,
  WhereLoop *pLoop,
  LogEst nRow
){
  WhereTerm *pTerm, *pX;
  Bitmask notAllowed = ~(pLoop->prereq|pLoop->maskSelf);
  int i, j;
  LogEst iReduce = 0;

  assert( (pLoop->wsFlags & WHERE_AUTO_INDEX)==0 );
  for(i=pWC->nBase, pTerm=pWC->a; i>0; i--, pTerm++){
    assert( pTerm!=0 );
    if( (pTerm->prereqAll & notAllowed)!=0 ) continue;
    if( (pTerm->prereqAll & pLoop->maskSelf)==0 ) continue;
    if( (pTerm->wtFlags & TERM_VIRTUAL)!=0 ) continue;
    for(j=pLoop->nLTerm-1; j>=0; j--){
      pX = pLoop->aLTerm[j];
      if( pX==0 ) continue;
      if( pX==pTerm ) break;
      if( pX->iParent>=0 && (&pWC->a[pX->iParent])==pTerm ) break;
    }
    if( j<0 ){
      if( pLoop->maskSelf==pTerm->prereqAll ){


        if( (pTerm->eOperator & 0x3f)!=0
         || (pWC->pWInfo->pTabList->a[pLoop->iTab].fg.jointype
                  & (JT_LEFT|JT_LTORJ))==0
        ){
          pLoop->wsFlags |= WHERE_SELFCULL;
        }
      }
      if( pTerm->truthProb<=0 ){


        pLoop->nOut += pTerm->truthProb;
      }else{


        pLoop->nOut--;
        if( (pTerm->eOperator&(WO_EQ|WO_IS))!=0
         && (pTerm->wtFlags & TERM_HIGHTRUTH)==0
        ){
          Expr *pRight = pTerm->pExpr->pRight;
          int k = 0;
          testcase( pTerm->pExpr->op==TK_IS );
          if( sqlite3ExprIsInteger(pRight, &k) && k>=(-1) && k<=1 ){
            k = 10;
          }else{
            k = 20;
          }
          if( iReduce<k ){
            pTerm->wtFlags |= TERM_HEURTRUTH;
            iReduce = k;
          }
        }
      }
    }
  }
  if( pLoop->nOut > nRow-iReduce ){
    pLoop->nOut = nRow - iReduce;
  }
}
