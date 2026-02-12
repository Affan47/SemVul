static int whereLoopAddVirtual(
  WhereLoopBuilder *pBuilder,
  Bitmask mPrereq,
  Bitmask mUnusable
){
  int rc = SQLITE_OK;
  WhereInfo *pWInfo;
  Parse *pParse;
  WhereClause *pWC;
  SrcItem *pSrc;
  sqlite3_index_info *p;
  int nConstraint;
  int bIn;
  WhereLoop *pNew;
  Bitmask mBest;
  u16 mNoOmit;
  int bRetry = 0;

  assert( (mPrereq & mUnusable)==0 );
  pWInfo = pBuilder->pWInfo;
  pParse = pWInfo->pParse;
  pWC = pBuilder->pWC;
  pNew = pBuilder->pNew;
  pSrc = &pWInfo->pTabList->a[pNew->iTab];
  assert( IsVirtual(pSrc->pTab) );
  p = allocateIndexInfo(pWInfo, pWC, mUnusable, pSrc, &mNoOmit);
  if( p==0 ) return SQLITE_NOMEM_BKPT;
  pNew->rSetup = 0;
  pNew->wsFlags = WHERE_VIRTUALTABLE;
  pNew->nLTerm = 0;
  pNew->u.vtab.needFree = 0;
  nConstraint = p->nConstraint;
  if( whereLoopResize(pParse->db, pNew, nConstraint) ){
    freeIndexInfo(pParse->db, p);
    return SQLITE_NOMEM_BKPT;
  }


  WHERETRACE(0x800, ("BEGIN %s.addVirtual()\n", pSrc->pTab->zName));
  WHERETRACE(0x40, ("  VirtualOne: all usable\n"));
  rc = whereLoopAddVirtualOne(
      pBuilder, mPrereq, ALLBITS, 0, p, mNoOmit, &bIn, &bRetry
  );
  if( bRetry ){
    assert( rc==SQLITE_OK );
    rc = whereLoopAddVirtualOne(
        pBuilder, mPrereq, ALLBITS, 0, p, mNoOmit, &bIn, 0
    );
  }


  if( rc==SQLITE_OK && ((mBest = (pNew->prereq & ~mPrereq))!=0 || bIn) ){
    int seenZero = 0;
    int seenZeroNoIN = 0;
    Bitmask mPrev = 0;
    Bitmask mBestNoIn = 0;


    if( bIn ){
      WHERETRACE(0x40, ("  VirtualOne: all usable w/o IN\n"));
      rc = whereLoopAddVirtualOne(
          pBuilder, mPrereq, ALLBITS, WO_IN, p, mNoOmit, &bIn, 0);
      assert( bIn==0 );
      mBestNoIn = pNew->prereq & ~mPrereq;
      if( mBestNoIn==0 ){
        seenZero = 1;
        seenZeroNoIN = 1;
      }
    }


    while( rc==SQLITE_OK ){
      int i;
      Bitmask mNext = ALLBITS;
      assert( mNext>0 );
      for(i=0; i<nConstraint; i++){
        Bitmask mThis = (
            pWC->a[p->aConstraint[i].iTermOffset].prereqRight & ~mPrereq
        );
        if( mThis>mPrev && mThis<mNext ) mNext = mThis;
      }
      mPrev = mNext;
      if( mNext==ALLBITS ) break;
      if( mNext==mBest || mNext==mBestNoIn ) continue;
      WHERETRACE(0x40, ("  VirtualOne: mPrev=%04llx mNext=%04llx\n",
                       (sqlite3_uint64)mPrev, (sqlite3_uint64)mNext));
      rc = whereLoopAddVirtualOne(
          pBuilder, mPrereq, mNext|mPrereq, 0, p, mNoOmit, &bIn, 0);
      if( pNew->prereq==mPrereq ){
        seenZero = 1;
        if( bIn==0 ) seenZeroNoIN = 1;
      }
    }


    if( rc==SQLITE_OK && seenZero==0 ){
      WHERETRACE(0x40, ("  VirtualOne: all disabled\n"));
      rc = whereLoopAddVirtualOne(
          pBuilder, mPrereq, mPrereq, 0, p, mNoOmit, &bIn, 0);
      if( bIn==0 ) seenZeroNoIN = 1;
    }


    if( rc==SQLITE_OK && seenZeroNoIN==0 ){
      WHERETRACE(0x40, ("  VirtualOne: all disabled and w/o IN\n"));
      rc = whereLoopAddVirtualOne(
          pBuilder, mPrereq, mPrereq, WO_IN, p, mNoOmit, &bIn, 0);
    }
  }

  if( p->needToFreeIdxStr ) sqlite3_free(p->idxStr);
  freeIndexInfo(pParse->db, p);
  WHERETRACE(0x800, ("END %s.addVirtual(), rc=%d\n", pSrc->pTab->zName, rc));
  return rc;
}
