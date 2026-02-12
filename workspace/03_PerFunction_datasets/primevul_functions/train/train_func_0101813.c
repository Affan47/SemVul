static int fts3EvalSelectDeferred(
  Fts3Cursor *pCsr,
  Fts3Expr *pRoot,
  Fts3TokenAndCost *aTC,
  int nTC
){
  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
  int nDocSize = 0;
  int rc = SQLITE_OK;
  int ii;
  int nOvfl = 0;
  int nToken = 0;

  int nMinEst = 0;
  int nLoad4 = 1;


  if( pTab->zContentTbl ){
    return SQLITE_OK;
  }


  for(ii=0; ii<nTC; ii++){
    if( aTC[ii].pRoot==pRoot ){
      nOvfl += aTC[ii].nOvfl;
      nToken++;
    }
  }
  if( nOvfl==0 || nToken<2 ) return SQLITE_OK;


  rc = fts3EvalAverageDocsize(pCsr, &nDocSize);
  assert( rc!=SQLITE_OK || nDocSize>0 );


  for(ii=0; ii<nToken && rc==SQLITE_OK; ii++){
    int iTC;
    Fts3TokenAndCost *pTC = 0;


    for(iTC=0; iTC<nTC; iTC++){
      if( aTC[iTC].pToken && aTC[iTC].pRoot==pRoot
       && (!pTC || aTC[iTC].nOvfl<pTC->nOvfl)
      ){
        pTC = &aTC[iTC];
      }
    }
    assert( pTC );

    if( ii && pTC->nOvfl>=((nMinEst+(nLoad4/4)-1)/(nLoad4/4))*nDocSize ){


      Fts3PhraseToken *pToken = pTC->pToken;
      rc = sqlite3Fts3DeferToken(pCsr, pToken, pTC->iCol);
      fts3SegReaderCursorFree(pToken->pSegcsr);
      pToken->pSegcsr = 0;
    }else{


      if( ii<12 ) nLoad4 = nLoad4*4;

      if( ii==0 || (pTC->pPhrase->nToken>1 && ii!=nToken-1) ){


        Fts3PhraseToken *pToken = pTC->pToken;
        int nList = 0;
        char *pList = 0;
        rc = fts3TermSelect(pTab, pToken, pTC->iCol, &nList, &pList);
        assert( rc==SQLITE_OK || pList==0 );
        if( rc==SQLITE_OK ){
          int nCount;
          fts3EvalPhraseMergeToken(pTab, pTC->pPhrase, pTC->iToken,pList,nList);
          nCount = fts3DoclistCountDocids(
              pTC->pPhrase->doclist.aAll, pTC->pPhrase->doclist.nAll
          );
          if( ii==0 || nCount<nMinEst ) nMinEst = nCount;
        }
      }
    }
    pTC->pToken = 0;
  }

  return rc;
}
