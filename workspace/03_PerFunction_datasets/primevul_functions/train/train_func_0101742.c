static int fts3EvalIncrPhraseNext(
  Fts3Cursor *pCsr,
  Fts3Phrase *p,
  u8 *pbEof
){
  int rc = SQLITE_OK;
  Fts3Doclist *pDL = &p->doclist;
  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
  u8 bEof = 0;


  assert( p->bIncr==1 );

  if( p->nToken==1 && p->bIncr ){
    rc = sqlite3Fts3MsrIncrNext(pTab, p->aToken[0].pSegcsr,
        &pDL->iDocid, &pDL->pList, &pDL->nList
    );
    if( pDL->pList==0 ) bEof = 1;
  }else{
    int bDescDoclist = pCsr->bDesc;
    struct TokenDoclist a[MAX_INCR_PHRASE_TOKENS];

    memset(a, 0, sizeof(a));
    assert( p->nToken<=MAX_INCR_PHRASE_TOKENS );
    assert( p->iDoclistToken<MAX_INCR_PHRASE_TOKENS );

    while( bEof==0 ){
      int bMaxSet = 0;
      sqlite3_int64 iMax = 0;
      int i;


      for(i=0; rc==SQLITE_OK && i<p->nToken && bEof==0; i++){
        rc = incrPhraseTokenNext(pTab, p, i, &a[i], &bEof);
        if( a[i].bIgnore==0 && (bMaxSet==0 || DOCID_CMP(iMax, a[i].iDocid)<0) ){
          iMax = a[i].iDocid;
          bMaxSet = 1;
        }
      }
      assert( rc!=SQLITE_OK || (p->nToken>=1 && a[p->nToken-1].bIgnore==0) );
      assert( rc!=SQLITE_OK || bMaxSet );


      for(i=0; i<p->nToken; i++){
        while( rc==SQLITE_OK && bEof==0
            && a[i].bIgnore==0 && DOCID_CMP(a[i].iDocid, iMax)<0
        ){
          rc = incrPhraseTokenNext(pTab, p, i, &a[i], &bEof);
          if( DOCID_CMP(a[i].iDocid, iMax)>0 ){
            iMax = a[i].iDocid;
            i = 0;
          }
        }
      }


      if( bEof==0 ){
        int nList = 0;
        int nByte = a[p->nToken-1].nList;
        char *aDoclist = sqlite3_malloc(nByte+1);
        if( !aDoclist ) return SQLITE_NOMEM;
        memcpy(aDoclist, a[p->nToken-1].pList, nByte+1);

        for(i=0; i<(p->nToken-1); i++){
          if( a[i].bIgnore==0 ){
            char *pL = a[i].pList;
            char *pR = aDoclist;
            char *pOut = aDoclist;
            int nDist = p->nToken-1-i;
            int res = fts3PoslistPhraseMerge(&pOut, nDist, 0, 1, &pL, &pR);
            if( res==0 ) break;
            nList = (int)(pOut - aDoclist);
          }
        }
        if( i==(p->nToken-1) ){
          pDL->iDocid = iMax;
          pDL->pList = aDoclist;
          pDL->nList = nList;
          pDL->bFreeList = 1;
          break;
        }
        sqlite3_free(aDoclist);
      }
    }
  }

  *pbEof = bEof;
  return rc;
}
