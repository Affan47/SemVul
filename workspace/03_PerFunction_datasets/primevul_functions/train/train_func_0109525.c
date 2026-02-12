static int whereLoopAddBtreeIndex(
  WhereLoopBuilder *pBuilder,
  SrcItem *pSrc,
  Index *pProbe,
  LogEst nInMul
){
  WhereInfo *pWInfo = pBuilder->pWInfo;
  Parse *pParse = pWInfo->pParse;
  sqlite3 *db = pParse->db;
  WhereLoop *pNew;
  WhereTerm *pTerm;
  int opMask;
  WhereScan scan;
  Bitmask saved_prereq;
  u16 saved_nLTerm;
  u16 saved_nEq;
  u16 saved_nBtm;
  u16 saved_nTop;
  u16 saved_nSkip;
  u32 saved_wsFlags;
  LogEst saved_nOut;
  int rc = SQLITE_OK;
  LogEst rSize;
  LogEst rLogSize;
  WhereTerm *pTop = 0, *pBtm = 0;

  pNew = pBuilder->pNew;
  if( db->mallocFailed ) return SQLITE_NOMEM_BKPT;
  WHERETRACE(0x800, ("BEGIN %s.addBtreeIdx(%s), nEq=%d, nSkip=%d, rRun=%d\n",
                     pProbe->pTable->zName,pProbe->zName,
                     pNew->u.btree.nEq, pNew->nSkip, pNew->rRun));

  assert( (pNew->wsFlags & WHERE_VIRTUALTABLE)==0 );
  assert( (pNew->wsFlags & WHERE_TOP_LIMIT)==0 );
  if( pNew->wsFlags & WHERE_BTM_LIMIT ){
    opMask = WO_LT|WO_LE;
  }else{
    assert( pNew->u.btree.nBtm==0 );
    opMask = WO_EQ|WO_IN|WO_GT|WO_GE|WO_LT|WO_LE|WO_ISNULL|WO_IS;
  }
  if( pProbe->bUnordered ) opMask &= ~(WO_GT|WO_GE|WO_LT|WO_LE);

  assert( pNew->u.btree.nEq<pProbe->nColumn );
  assert( pNew->u.btree.nEq<pProbe->nKeyCol
       || pProbe->idxType!=SQLITE_IDXTYPE_PRIMARYKEY );

  saved_nEq = pNew->u.btree.nEq;
  saved_nBtm = pNew->u.btree.nBtm;
  saved_nTop = pNew->u.btree.nTop;
  saved_nSkip = pNew->nSkip;
  saved_nLTerm = pNew->nLTerm;
  saved_wsFlags = pNew->wsFlags;
  saved_prereq = pNew->prereq;
  saved_nOut = pNew->nOut;
  pTerm = whereScanInit(&scan, pBuilder->pWC, pSrc->iCursor, saved_nEq,
                        opMask, pProbe);
  pNew->rSetup = 0;
  rSize = pProbe->aiRowLogEst[0];
  rLogSize = estLog(rSize);
  for(; rc==SQLITE_OK && pTerm!=0; pTerm = whereScanNext(&scan)){
    u16 eOp = pTerm->eOperator;
    LogEst rCostIdx;
    LogEst nOutUnadjusted;
    int nIn = 0;
#ifdef SQLITE_ENABLE_STAT4
    int nRecValid = pBuilder->nRecValid;
#endif
    if( (eOp==WO_ISNULL || (pTerm->wtFlags&TERM_VNULL)!=0)
     && indexColumnNotNull(pProbe, saved_nEq)
    ){
      continue;
    }
    if( pTerm->prereqRight & pNew->maskSelf ) continue;


    if( pTerm->wtFlags & TERM_LIKEOPT && pTerm->eOperator==WO_LT ) continue;


    if( (pSrc->fg.jointype & (JT_LEFT|JT_LTORJ|JT_RIGHT))!=0 ){
      testcase( (pSrc->fg.jointype & (JT_LEFT|JT_LTORJ|JT_RIGHT))==JT_LEFT );
      testcase( (pSrc->fg.jointype & (JT_LEFT|JT_LTORJ|JT_RIGHT))==JT_RIGHT );
      testcase( (pSrc->fg.jointype & (JT_LEFT|JT_LTORJ|JT_RIGHT))==JT_LTORJ );
      testcase( ExprHasProperty(pTerm->pExpr, EP_OuterON) )
      testcase( ExprHasProperty(pTerm->pExpr, EP_InnerON) );
      if( !ExprHasProperty(pTerm->pExpr, EP_OuterON|EP_InnerON)
       || pTerm->pExpr->w.iJoin != pSrc->iCursor
      ){
        continue;
      }
    }

    if( IsUniqueIndex(pProbe) && saved_nEq==pProbe->nKeyCol-1 ){
      pBuilder->bldFlags1 |= SQLITE_BLDF1_UNIQUE;
    }else{
      pBuilder->bldFlags1 |= SQLITE_BLDF1_INDEXED;
    }
    pNew->wsFlags = saved_wsFlags;
    pNew->u.btree.nEq = saved_nEq;
    pNew->u.btree.nBtm = saved_nBtm;
    pNew->u.btree.nTop = saved_nTop;
    pNew->nLTerm = saved_nLTerm;
    if( whereLoopResize(db, pNew, pNew->nLTerm+1) ) break;
    pNew->aLTerm[pNew->nLTerm++] = pTerm;
    pNew->prereq = (saved_prereq | pTerm->prereqRight) & ~pNew->maskSelf;

    assert( nInMul==0
        || (pNew->wsFlags & WHERE_COLUMN_NULL)!=0
        || (pNew->wsFlags & WHERE_COLUMN_IN)!=0
        || (pNew->wsFlags & WHERE_SKIPSCAN)!=0
    );

    if( eOp & WO_IN ){
      Expr *pExpr = pTerm->pExpr;
      if( ExprUseXSelect(pExpr) ){

        int i;
        nIn = 46;  assert( 46==sqlite3LogEst(25) );


        for(i=0; i<pNew->nLTerm-1; i++){
          if( pNew->aLTerm[i] && pNew->aLTerm[i]->pExpr==pExpr ) nIn = 0;
        }
      }else if( ALWAYS(pExpr->x.pList && pExpr->x.pList->nExpr) ){

        nIn = sqlite3LogEst(pExpr->x.pList->nExpr);
      }
      if( pProbe->hasStat1 && rLogSize>=10 ){
        LogEst M, logK, x;


        M = pProbe->aiRowLogEst[saved_nEq];
        logK = estLog(nIn);

        x = M + logK + 10 - (nIn + rLogSize);
        if( x>=0 ){
          WHERETRACE(0x40,
            ("IN operator (N=%d M=%d logK=%d nIn=%d rLogSize=%d x=%d) "
             "prefers indexed lookup\n",
             saved_nEq, M, logK, nIn, rLogSize, x));
        }else if( nInMul<2 && OptimizationEnabled(db, SQLITE_SeekScan) ){
          WHERETRACE(0x40,
            ("IN operator (N=%d M=%d logK=%d nIn=%d rLogSize=%d x=%d"
             " nInMul=%d) prefers skip-scan\n",
             saved_nEq, M, logK, nIn, rLogSize, x, nInMul));
          pNew->wsFlags |= WHERE_IN_SEEKSCAN;
        }else{
          WHERETRACE(0x40,
            ("IN operator (N=%d M=%d logK=%d nIn=%d rLogSize=%d x=%d"
             " nInMul=%d) prefers normal scan\n",
             saved_nEq, M, logK, nIn, rLogSize, x, nInMul));
          continue;
        }
      }
      pNew->wsFlags |= WHERE_COLUMN_IN;
    }else if( eOp & (WO_EQ|WO_IS) ){
      int iCol = pProbe->aiColumn[saved_nEq];
      pNew->wsFlags |= WHERE_COLUMN_EQ;
      assert( saved_nEq==pNew->u.btree.nEq );
      if( iCol==XN_ROWID
       || (iCol>=0 && nInMul==0 && saved_nEq==pProbe->nKeyCol-1)
      ){
        if( iCol==XN_ROWID || pProbe->uniqNotNull
         || (pProbe->nKeyCol==1 && pProbe->onError && eOp==WO_EQ)
        ){
          pNew->wsFlags |= WHERE_ONEROW;
        }else{
          pNew->wsFlags |= WHERE_UNQ_WANTED;
        }
      }
      if( scan.iEquiv>1 ) pNew->wsFlags |= WHERE_TRANSCONS;
    }else if( eOp & WO_ISNULL ){
      pNew->wsFlags |= WHERE_COLUMN_NULL;
    }else if( eOp & (WO_GT|WO_GE) ){
      testcase( eOp & WO_GT );
      testcase( eOp & WO_GE );
      pNew->wsFlags |= WHERE_COLUMN_RANGE|WHERE_BTM_LIMIT;
      pNew->u.btree.nBtm = whereRangeVectorLen(
          pParse, pSrc->iCursor, pProbe, saved_nEq, pTerm
      );
      pBtm = pTerm;
      pTop = 0;
      if( pTerm->wtFlags & TERM_LIKEOPT ){


        pTop = &pTerm[1];
        assert( (pTop-(pTerm->pWC->a))<pTerm->pWC->nTerm );
        assert( pTop->wtFlags & TERM_LIKEOPT );
        assert( pTop->eOperator==WO_LT );
        if( whereLoopResize(db, pNew, pNew->nLTerm+1) ) break;
        pNew->aLTerm[pNew->nLTerm++] = pTop;
        pNew->wsFlags |= WHERE_TOP_LIMIT;
        pNew->u.btree.nTop = 1;
      }
    }else{
      assert( eOp & (WO_LT|WO_LE) );
      testcase( eOp & WO_LT );
      testcase( eOp & WO_LE );
      pNew->wsFlags |= WHERE_COLUMN_RANGE|WHERE_TOP_LIMIT;
      pNew->u.btree.nTop = whereRangeVectorLen(
          pParse, pSrc->iCursor, pProbe, saved_nEq, pTerm
      );
      pTop = pTerm;
      pBtm = (pNew->wsFlags & WHERE_BTM_LIMIT)!=0 ?
                     pNew->aLTerm[pNew->nLTerm-2] : 0;
    }


    assert( pNew->nOut==saved_nOut );
    if( pNew->wsFlags & WHERE_COLUMN_RANGE ){


      whereRangeScanEst(pParse, pBuilder, pBtm, pTop, pNew);
    }else{
      int nEq = ++pNew->u.btree.nEq;
      assert( eOp & (WO_ISNULL|WO_EQ|WO_IN|WO_IS) );

      assert( pNew->nOut==saved_nOut );
      if( pTerm->truthProb<=0 && pProbe->aiColumn[saved_nEq]>=0 ){
        assert( (eOp & WO_IN) || nIn==0 );
        testcase( eOp & WO_IN );
        pNew->nOut += pTerm->truthProb;
        pNew->nOut -= nIn;
      }else{
#ifdef SQLITE_ENABLE_STAT4
        tRowcnt nOut = 0;
        if( nInMul==0
         && pProbe->nSample
         && ALWAYS(pNew->u.btree.nEq<=pProbe->nSampleCol)
         && ((eOp & WO_IN)==0 || ExprUseXList(pTerm->pExpr))
         && OptimizationEnabled(db, SQLITE_Stat4)
        ){
          Expr *pExpr = pTerm->pExpr;
          if( (eOp & (WO_EQ|WO_ISNULL|WO_IS))!=0 ){
            testcase( eOp & WO_EQ );
            testcase( eOp & WO_IS );
            testcase( eOp & WO_ISNULL );
            rc = whereEqualScanEst(pParse, pBuilder, pExpr->pRight, &nOut);
          }else{
            rc = whereInScanEst(pParse, pBuilder, pExpr->x.pList, &nOut);
          }
          if( rc==SQLITE_NOTFOUND ) rc = SQLITE_OK;
          if( rc!=SQLITE_OK ) break;
          if( nOut ){
            pNew->nOut = sqlite3LogEst(nOut);
            if( nEq==1


             && pNew->nOut+10 > pProbe->aiRowLogEst[0]
            ){
#if WHERETRACE_ENABLED
              if( sqlite3WhereTrace & 0x01 ){
                sqlite3DebugPrintf(
                   "STAT4 determines term has low selectivity:\n");
                sqlite3WhereTermPrint(pTerm, 999);
              }
#endif
              pTerm->wtFlags |= TERM_HIGHTRUTH;
              if( pTerm->wtFlags & TERM_HEURTRUTH ){


                pBuilder->bldFlags2 |= SQLITE_BLDF2_2NDPASS;
              }
            }
            if( pNew->nOut>saved_nOut ) pNew->nOut = saved_nOut;
            pNew->nOut -= nIn;
          }
        }
        if( nOut==0 )
#endif
        {
          pNew->nOut += (pProbe->aiRowLogEst[nEq] - pProbe->aiRowLogEst[nEq-1]);
          if( eOp & WO_ISNULL ){


            pNew->nOut += 10;
          }
        }
      }
    }


    assert( pSrc->pTab->szTabRow>0 );
    rCostIdx = pNew->nOut + 1 + (15*pProbe->szIdxRow)/pSrc->pTab->szTabRow;
    pNew->rRun = sqlite3LogEstAdd(rLogSize, rCostIdx);
    if( (pNew->wsFlags & (WHERE_IDX_ONLY|WHERE_IPK))==0 ){
      pNew->rRun = sqlite3LogEstAdd(pNew->rRun, pNew->nOut + 16);
    }
    ApplyCostMultiplier(pNew->rRun, pProbe->pTable->costMult);

    nOutUnadjusted = pNew->nOut;
    pNew->rRun += nInMul + nIn;
    pNew->nOut += nInMul + nIn;
    whereLoopOutputAdjust(pBuilder->pWC, pNew, rSize);
    rc = whereLoopInsert(pBuilder, pNew);

    if( pNew->wsFlags & WHERE_COLUMN_RANGE ){
      pNew->nOut = saved_nOut;
    }else{
      pNew->nOut = nOutUnadjusted;
    }

    if( (pNew->wsFlags & WHERE_TOP_LIMIT)==0
     && pNew->u.btree.nEq<pProbe->nColumn
     && (pNew->u.btree.nEq<pProbe->nKeyCol ||
           pProbe->idxType!=SQLITE_IDXTYPE_PRIMARYKEY)
    ){
      whereLoopAddBtreeIndex(pBuilder, pSrc, pProbe, nInMul+nIn);
    }
    pNew->nOut = saved_nOut;
#ifdef SQLITE_ENABLE_STAT4
    pBuilder->nRecValid = nRecValid;
#endif
  }
  pNew->prereq = saved_prereq;
  pNew->u.btree.nEq = saved_nEq;
  pNew->u.btree.nBtm = saved_nBtm;
  pNew->u.btree.nTop = saved_nTop;
  pNew->nSkip = saved_nSkip;
  pNew->wsFlags = saved_wsFlags;
  pNew->nOut = saved_nOut;
  pNew->nLTerm = saved_nLTerm;


  assert( 42==sqlite3LogEst(18) );
  if( saved_nEq==saved_nSkip
   && saved_nEq+1<pProbe->nKeyCol
   && saved_nEq==pNew->nLTerm
   && pProbe->noSkipScan==0
   && pProbe->hasStat1!=0
   && OptimizationEnabled(db, SQLITE_SkipScan)
   && pProbe->aiRowLogEst[saved_nEq+1]>=42
   && (rc = whereLoopResize(db, pNew, pNew->nLTerm+1))==SQLITE_OK
  ){
    LogEst nIter;
    pNew->u.btree.nEq++;
    pNew->nSkip++;
    pNew->aLTerm[pNew->nLTerm++] = 0;
    pNew->wsFlags |= WHERE_SKIPSCAN;
    nIter = pProbe->aiRowLogEst[saved_nEq] - pProbe->aiRowLogEst[saved_nEq+1];
    pNew->nOut -= nIter;


    nIter += 5;
    whereLoopAddBtreeIndex(pBuilder, pSrc, pProbe, nIter + nInMul);
    pNew->nOut = saved_nOut;
    pNew->u.btree.nEq = saved_nEq;
    pNew->nSkip = saved_nSkip;
    pNew->wsFlags = saved_wsFlags;
  }

  WHERETRACE(0x800, ("END %s.addBtreeIdx(%s), nEq=%d, rc=%d\n",
                      pProbe->pTable->zName, pProbe->zName, saved_nEq, rc));
  return rc;
}
