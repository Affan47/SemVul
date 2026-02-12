static void selectInnerLoop(
  Parse *pParse,
  Select *p,
  int srcTab,
  SortCtx *pSort,
  DistinctCtx *pDistinct,
  SelectDest *pDest,
  int iContinue,
  int iBreak
){
  Vdbe *v = pParse->pVdbe;
  int i;
  int hasDistinct;
  int eDest = pDest->eDest;
  int iParm = pDest->iSDParm;
  int nResultCol;
  int nPrefixReg = 0;
  RowLoadInfo sRowLoadInfo;


  int regResult;
  int regOrig;

  assert( v );
  assert( p->pEList!=0 );
  hasDistinct = pDistinct ? pDistinct->eTnctType : WHERE_DISTINCT_NOOP;
  if( pSort && pSort->pOrderBy==0 ) pSort = 0;
  if( pSort==0 && !hasDistinct ){
    assert( iContinue!=0 );
    codeOffset(v, p->iOffset, iContinue);
  }


  nResultCol = p->pEList->nExpr;

  if( pDest->iSdst==0 ){
    if( pSort ){
      nPrefixReg = pSort->pOrderBy->nExpr;
      if( !(pSort->sortFlags & SORTFLAG_UseSorter) ) nPrefixReg++;
      pParse->nMem += nPrefixReg;
    }
    pDest->iSdst = pParse->nMem+1;
    pParse->nMem += nResultCol;
  }else if( pDest->iSdst+nResultCol > pParse->nMem ){


    pParse->nMem += nResultCol;
  }
  pDest->nSdst = nResultCol;
  regOrig = regResult = pDest->iSdst;
  if( srcTab>=0 ){
    for(i=0; i<nResultCol; i++){
      sqlite3VdbeAddOp3(v, OP_Column, srcTab, i, regResult+i);
      VdbeComment((v, "%s", p->pEList->a[i].zName));
    }
  }else if( eDest!=SRT_Exists ){
#ifdef SQLITE_ENABLE_SORTER_REFERENCES
    ExprList *pExtra = 0;
#endif


    u8 ecelFlags;
    ExprList *pEList;
    if( eDest==SRT_Mem || eDest==SRT_Output || eDest==SRT_Coroutine ){
      ecelFlags = SQLITE_ECEL_DUP;
    }else{
      ecelFlags = 0;
    }
    if( pSort && hasDistinct==0 && eDest!=SRT_EphemTab && eDest!=SRT_Table ){


      ecelFlags |= (SQLITE_ECEL_OMITREF|SQLITE_ECEL_REF);

      for(i=pSort->nOBSat; i<pSort->pOrderBy->nExpr; i++){
        int j;
        if( (j = pSort->pOrderBy->a[i].u.x.iOrderByCol)>0 ){
          p->pEList->a[j-1].u.x.iOrderByCol = i+1-pSort->nOBSat;
        }
      }
#ifdef SQLITE_ENABLE_SORTER_REFERENCES
      selectExprDefer(pParse, pSort, p->pEList, &pExtra);
      if( pExtra && pParse->db->mallocFailed==0 ){


        VdbeOp *pOp = sqlite3VdbeGetOp(v, pSort->addrSortIndex);
        pOp->p2 += (pExtra->nExpr - pSort->nDefer);
        pOp->p4.pKeyInfo->nAllField += (pExtra->nExpr - pSort->nDefer);
        pParse->nMem += pExtra->nExpr;
      }
#endif


      pEList = p->pEList;
      for(i=0; i<pEList->nExpr; i++){
        if( pEList->a[i].u.x.iOrderByCol>0
#ifdef SQLITE_ENABLE_SORTER_REFERENCES
         || pEList->a[i].bSorterRef
#endif
        ){
          nResultCol--;
          regOrig = 0;
        }
      }

      testcase( regOrig );
      testcase( eDest==SRT_Set );
      testcase( eDest==SRT_Mem );
      testcase( eDest==SRT_Coroutine );
      testcase( eDest==SRT_Output );
      assert( eDest==SRT_Set || eDest==SRT_Mem
           || eDest==SRT_Coroutine || eDest==SRT_Output );
    }
    sRowLoadInfo.regResult = regResult;
    sRowLoadInfo.ecelFlags = ecelFlags;
#ifdef SQLITE_ENABLE_SORTER_REFERENCES
    sRowLoadInfo.pExtra = pExtra;
    sRowLoadInfo.regExtraResult = regResult + nResultCol;
    if( pExtra ) nResultCol += pExtra->nExpr;
#endif
    if( p->iLimit
     && (ecelFlags & SQLITE_ECEL_OMITREF)!=0
     && nPrefixReg>0
    ){
      assert( pSort!=0 );
      assert( hasDistinct==0 );
      pSort->pDeferredRowLoad = &sRowLoadInfo;
      regOrig = 0;
    }else{
      innerLoopLoadRow(pParse, p, &sRowLoadInfo);
    }
  }


  if( hasDistinct ){
    switch( pDistinct->eTnctType ){
      case WHERE_DISTINCT_ORDERED: {
        VdbeOp *pOp;
        int iJump;
        int regPrev;


        regPrev = pParse->nMem+1;
        pParse->nMem += nResultCol;


        sqlite3VdbeChangeToNoop(v, pDistinct->addrTnct);
        pOp = sqlite3VdbeGetOp(v, pDistinct->addrTnct);
        pOp->opcode = OP_Null;
        pOp->p1 = 1;
        pOp->p2 = regPrev;

        iJump = sqlite3VdbeCurrentAddr(v) + nResultCol;
        for(i=0; i<nResultCol; i++){
          CollSeq *pColl = sqlite3ExprCollSeq(pParse, p->pEList->a[i].pExpr);
          if( i<nResultCol-1 ){
            sqlite3VdbeAddOp3(v, OP_Ne, regResult+i, iJump, regPrev+i);
            VdbeCoverage(v);
          }else{
            sqlite3VdbeAddOp3(v, OP_Eq, regResult+i, iContinue, regPrev+i);
            VdbeCoverage(v);
           }
          sqlite3VdbeChangeP4(v, -1, (const char *)pColl, P4_COLLSEQ);
          sqlite3VdbeChangeP5(v, SQLITE_NULLEQ);
        }
        assert( sqlite3VdbeCurrentAddr(v)==iJump || pParse->db->mallocFailed );
        sqlite3VdbeAddOp3(v, OP_Copy, regResult, regPrev, nResultCol-1);
        break;
      }

      case WHERE_DISTINCT_UNIQUE: {
        sqlite3VdbeChangeToNoop(v, pDistinct->addrTnct);
        break;
      }

      default: {
        assert( pDistinct->eTnctType==WHERE_DISTINCT_UNORDERED );
        codeDistinct(pParse, pDistinct->tabTnct, iContinue, nResultCol,
                     regResult);
        break;
      }
    }
    if( pSort==0 ){
      codeOffset(v, p->iOffset, iContinue);
    }
  }

  switch( eDest ){


#ifndef SQLITE_OMIT_COMPOUND_SELECT
    case SRT_Union: {
      int r1;
      r1 = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp3(v, OP_MakeRecord, regResult, nResultCol, r1);
      sqlite3VdbeAddOp4Int(v, OP_IdxInsert, iParm, r1, regResult, nResultCol);
      sqlite3ReleaseTempReg(pParse, r1);
      break;
    }


    case SRT_Except: {
      sqlite3VdbeAddOp3(v, OP_IdxDelete, iParm, regResult, nResultCol);
      break;
    }
#endif


    case SRT_Fifo:
    case SRT_DistFifo:
    case SRT_Table:
    case SRT_EphemTab: {
      int r1 = sqlite3GetTempRange(pParse, nPrefixReg+1);
      testcase( eDest==SRT_Table );
      testcase( eDest==SRT_EphemTab );
      testcase( eDest==SRT_Fifo );
      testcase( eDest==SRT_DistFifo );
      sqlite3VdbeAddOp3(v, OP_MakeRecord, regResult, nResultCol, r1+nPrefixReg);
#ifndef SQLITE_OMIT_CTE
      if( eDest==SRT_DistFifo ){


        int addr = sqlite3VdbeCurrentAddr(v) + 4;
        sqlite3VdbeAddOp4Int(v, OP_Found, iParm+1, addr, r1, 0);
        VdbeCoverage(v);
        sqlite3VdbeAddOp4Int(v, OP_IdxInsert, iParm+1, r1,regResult,nResultCol);
        assert( pSort==0 );
      }
#endif
      if( pSort ){
        assert( regResult==regOrig );
        pushOntoSorter(pParse, pSort, p, r1+nPrefixReg, regOrig, 1, nPrefixReg);
      }else{
        int r2 = sqlite3GetTempReg(pParse);
        sqlite3VdbeAddOp2(v, OP_NewRowid, iParm, r2);
        sqlite3VdbeAddOp3(v, OP_Insert, iParm, r1, r2);
        sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
        sqlite3ReleaseTempReg(pParse, r2);
      }
      sqlite3ReleaseTempRange(pParse, r1, nPrefixReg+1);
      break;
    }

#ifndef SQLITE_OMIT_SUBQUERY


    case SRT_Set: {
      if( pSort ){


        pushOntoSorter(
            pParse, pSort, p, regResult, regOrig, nResultCol, nPrefixReg);
      }else{
        int r1 = sqlite3GetTempReg(pParse);
        assert( sqlite3Strlen30(pDest->zAffSdst)==nResultCol );
        sqlite3VdbeAddOp4(v, OP_MakeRecord, regResult, nResultCol,
            r1, pDest->zAffSdst, nResultCol);
        sqlite3ExprCacheAffinityChange(pParse, regResult, nResultCol);
        sqlite3VdbeAddOp4Int(v, OP_IdxInsert, iParm, r1, regResult, nResultCol);
        sqlite3ReleaseTempReg(pParse, r1);
      }
      break;
    }


    case SRT_Exists: {
      sqlite3VdbeAddOp2(v, OP_Integer, 1, iParm);

      break;
    }


    case SRT_Mem: {
      if( pSort ){
        assert( nResultCol<=pDest->nSdst );
        pushOntoSorter(
            pParse, pSort, p, regResult, regOrig, nResultCol, nPrefixReg);
      }else{
        assert( nResultCol==pDest->nSdst );
        assert( regResult==iParm );

      }
      break;
    }
#endif

    case SRT_Coroutine:
    case SRT_Output: {
      testcase( eDest==SRT_Coroutine );
      testcase( eDest==SRT_Output );
      if( pSort ){
        pushOntoSorter(pParse, pSort, p, regResult, regOrig, nResultCol,
                       nPrefixReg);
      }else if( eDest==SRT_Coroutine ){
        sqlite3VdbeAddOp1(v, OP_Yield, pDest->iSDParm);
      }else{
        sqlite3VdbeAddOp2(v, OP_ResultRow, regResult, nResultCol);
        sqlite3ExprCacheAffinityChange(pParse, regResult, nResultCol);
      }
      break;
    }

#ifndef SQLITE_OMIT_CTE


    case SRT_DistQueue:
    case SRT_Queue: {
      int nKey;
      int r1, r2, r3;
      int addrTest = 0;
      ExprList *pSO;
      pSO = pDest->pOrderBy;
      assert( pSO );
      nKey = pSO->nExpr;
      r1 = sqlite3GetTempReg(pParse);
      r2 = sqlite3GetTempRange(pParse, nKey+2);
      r3 = r2+nKey+1;
      if( eDest==SRT_DistQueue ){


        addrTest = sqlite3VdbeAddOp4Int(v, OP_Found, iParm+1, 0,
                                        regResult, nResultCol);
        VdbeCoverage(v);
      }
      sqlite3VdbeAddOp3(v, OP_MakeRecord, regResult, nResultCol, r3);
      if( eDest==SRT_DistQueue ){
        sqlite3VdbeAddOp2(v, OP_IdxInsert, iParm+1, r3);
        sqlite3VdbeChangeP5(v, OPFLAG_USESEEKRESULT);
      }
      for(i=0; i<nKey; i++){
        sqlite3VdbeAddOp2(v, OP_SCopy,
                          regResult + pSO->a[i].u.x.iOrderByCol - 1,
                          r2+i);
      }
      sqlite3VdbeAddOp2(v, OP_Sequence, iParm, r2+nKey);
      sqlite3VdbeAddOp3(v, OP_MakeRecord, r2, nKey+2, r1);
      sqlite3VdbeAddOp4Int(v, OP_IdxInsert, iParm, r1, r2, nKey+2);
      if( addrTest ) sqlite3VdbeJumpHere(v, addrTest);
      sqlite3ReleaseTempReg(pParse, r1);
      sqlite3ReleaseTempRange(pParse, r2, nKey+2);
      break;
    }
#endif


#if !defined(SQLITE_OMIT_TRIGGER)


    default: {
      assert( eDest==SRT_Discard );
      break;
    }
#endif
  }


  if( pSort==0 && p->iLimit ){
    sqlite3VdbeAddOp2(v, OP_DecrJumpZero, p->iLimit, iBreak); VdbeCoverage(v);
  }
}
