Bitmask sqlite3WhereCodeOneLoopStart(
  Parse *pParse,
  Vdbe *v,
  WhereInfo *pWInfo,
  int iLevel,
  WhereLevel *pLevel,
  Bitmask notReady
){
  int j, k;
  int iCur;
  int addrNxt;
  int bRev;
  WhereLoop *pLoop;
  WhereClause *pWC;
  WhereTerm *pTerm;
  sqlite3 *db;
  struct SrcList_item *pTabItem;
  int addrBrk;
  int addrHalt;
  int addrCont;
  int iRowidReg = 0;
  int iReleaseReg = 0;
  Index *pIdx = 0;
  int iLoop;

  pWC = &pWInfo->sWC;
  db = pParse->db;
  pLoop = pLevel->pWLoop;
  pTabItem = &pWInfo->pTabList->a[pLevel->iFrom];
  iCur = pTabItem->iCursor;
  pLevel->notReady = notReady & ~sqlite3WhereGetMask(&pWInfo->sMaskSet, iCur);
  bRev = (pWInfo->revMask>>iLevel)&1;
  VdbeModuleComment((v, "Begin WHERE-loop%d: %s",iLevel,pTabItem->pTab->zName));


  addrBrk = pLevel->addrBrk = pLevel->addrNxt = sqlite3VdbeMakeLabel(pParse);
  addrCont = pLevel->addrCont = sqlite3VdbeMakeLabel(pParse);


  assert( (pWInfo->wctrlFlags & WHERE_OR_SUBCLAUSE)
       || pLevel->iFrom>0 || (pTabItem[0].fg.jointype & JT_LEFT)==0
  );
  if( pLevel->iFrom>0 && (pTabItem[0].fg.jointype & JT_LEFT)!=0 ){
    pLevel->iLeftJoin = ++pParse->nMem;
    sqlite3VdbeAddOp2(v, OP_Integer, 0, pLevel->iLeftJoin);
    VdbeComment((v, "init LEFT JOIN no-match flag"));
  }


  for(j=iLevel; j>0 && pWInfo->a[j].iLeftJoin==0; j--){}
  addrHalt = pWInfo->a[j].addrBrk;


  if( pTabItem->fg.viaCoroutine ){
    int regYield = pTabItem->regReturn;
    sqlite3VdbeAddOp3(v, OP_InitCoroutine, regYield, 0, pTabItem->addrFillSub);
    pLevel->p2 =  sqlite3VdbeAddOp2(v, OP_Yield, regYield, addrBrk);
    VdbeCoverage(v);
    VdbeComment((v, "next row of %s", pTabItem->pTab->zName));
    pLevel->op = OP_Goto;
  }else

#ifndef SQLITE_OMIT_VIRTUALTABLE
  if(  (pLoop->wsFlags & WHERE_VIRTUALTABLE)!=0 ){


    int iReg;
    int addrNotFound;
    int nConstraint = pLoop->nLTerm;
    int iIn;

    iReg = sqlite3GetTempRange(pParse, nConstraint+2);
    addrNotFound = pLevel->addrBrk;
    for(j=0; j<nConstraint; j++){
      int iTarget = iReg+j+2;
      pTerm = pLoop->aLTerm[j];
      if( NEVER(pTerm==0) ) continue;
      if( pTerm->eOperator & WO_IN ){
        codeEqualityTerm(pParse, pTerm, pLevel, j, bRev, iTarget);
        addrNotFound = pLevel->addrNxt;
      }else{
        Expr *pRight = pTerm->pExpr->pRight;
        codeExprOrVector(pParse, pRight, iTarget, 1);
      }
    }
    sqlite3VdbeAddOp2(v, OP_Integer, pLoop->u.vtab.idxNum, iReg);
    sqlite3VdbeAddOp2(v, OP_Integer, nConstraint, iReg+1);
    sqlite3VdbeAddOp4(v, OP_VFilter, iCur, addrNotFound, iReg,
                      pLoop->u.vtab.idxStr,
                      pLoop->u.vtab.needFree ? P4_DYNAMIC : P4_STATIC);
    VdbeCoverage(v);
    pLoop->u.vtab.needFree = 0;
    pLevel->p1 = iCur;
    pLevel->op = pWInfo->eOnePass ? OP_Noop : OP_VNext;
    pLevel->p2 = sqlite3VdbeCurrentAddr(v);
    iIn = pLevel->u.in.nIn;
    for(j=nConstraint-1; j>=0; j--){
      pTerm = pLoop->aLTerm[j];
      if( (pTerm->eOperator & WO_IN)!=0 ) iIn--;
      if( j<16 && (pLoop->u.vtab.omitMask>>j)&1 ){
        disableTerm(pLevel, pTerm);
      }else if( (pTerm->eOperator & WO_IN)!=0
        && sqlite3ExprVectorSize(pTerm->pExpr->pLeft)==1
      ){
        Expr *pCompare;
        Expr *pRight;
        VdbeOp *pOp;


        assert( pLevel->u.in.aInLoop!=0 || db->mallocFailed );
        if( !db->mallocFailed ){
          assert( iIn>=0 && iIn<pLevel->u.in.nIn );
          pOp = sqlite3VdbeGetOp(v, pLevel->u.in.aInLoop[iIn].addrInTop);
          assert( pOp->opcode==OP_Column || pOp->opcode==OP_Rowid );
          assert( pOp->opcode!=OP_Column || pOp->p3==iReg+j+2 );
          assert( pOp->opcode!=OP_Rowid || pOp->p2==iReg+j+2 );
          testcase( pOp->opcode==OP_Rowid );
          sqlite3VdbeAddOp3(v, pOp->opcode, pOp->p1, pOp->p2, pOp->p3);
        }


        pCompare = sqlite3PExpr(pParse, TK_EQ, 0, 0);
        assert( pCompare!=0 || db->mallocFailed );
        if( pCompare ){
          pCompare->pLeft = pTerm->pExpr->pLeft;
          pCompare->pRight = pRight = sqlite3Expr(db, TK_REGISTER, 0);
          if( pRight ){
            pRight->iTable = iReg+j+2;
            sqlite3ExprIfFalse(pParse, pCompare, pLevel->addrCont, 0);
          }
          pCompare->pLeft = 0;
          sqlite3ExprDelete(db, pCompare);
        }
      }
    }
    assert( iIn==0 || db->mallocFailed );


  }else
#endif

  if( (pLoop->wsFlags & WHERE_IPK)!=0
   && (pLoop->wsFlags & (WHERE_COLUMN_IN|WHERE_COLUMN_EQ))!=0
  ){


    assert( pLoop->u.btree.nEq==1 );
    pTerm = pLoop->aLTerm[0];
    assert( pTerm!=0 );
    assert( pTerm->pExpr!=0 );
    testcase( pTerm->wtFlags & TERM_VIRTUAL );
    iReleaseReg = ++pParse->nMem;
    iRowidReg = codeEqualityTerm(pParse, pTerm, pLevel, 0, bRev, iReleaseReg);
    if( iRowidReg!=iReleaseReg ) sqlite3ReleaseTempReg(pParse, iReleaseReg);
    addrNxt = pLevel->addrNxt;
    sqlite3VdbeAddOp3(v, OP_SeekRowid, iCur, addrNxt, iRowidReg);
    VdbeCoverage(v);
    pLevel->op = OP_Noop;
    if( (pTerm->prereqAll & pLevel->notReady)==0 ){
      pTerm->wtFlags |= TERM_CODED;
    }
  }else if( (pLoop->wsFlags & WHERE_IPK)!=0
         && (pLoop->wsFlags & WHERE_COLUMN_RANGE)!=0
  ){


    int testOp = OP_Noop;
    int start;
    int memEndValue = 0;
    WhereTerm *pStart, *pEnd;

    j = 0;
    pStart = pEnd = 0;
    if( pLoop->wsFlags & WHERE_BTM_LIMIT ) pStart = pLoop->aLTerm[j++];
    if( pLoop->wsFlags & WHERE_TOP_LIMIT ) pEnd = pLoop->aLTerm[j++];
    assert( pStart!=0 || pEnd!=0 );
    if( bRev ){
      pTerm = pStart;
      pStart = pEnd;
      pEnd = pTerm;
    }
    codeCursorHint(pTabItem, pWInfo, pLevel, pEnd);
    if( pStart ){
      Expr *pX;
      int r1, rTemp;
      int op;


      const u8 aMoveOp[] = {
             OP_SeekGT,
             OP_SeekLE,
             OP_SeekLT,
             OP_SeekGE
      };
      assert( TK_LE==TK_GT+1 );
      assert( TK_LT==TK_GT+2 );
      assert( TK_GE==TK_GT+3 );

      assert( (pStart->wtFlags & TERM_VNULL)==0 );
      testcase( pStart->wtFlags & TERM_VIRTUAL );
      pX = pStart->pExpr;
      assert( pX!=0 );
      testcase( pStart->leftCursor!=iCur );
      if( sqlite3ExprIsVector(pX->pRight) ){
        r1 = rTemp = sqlite3GetTempReg(pParse);
        codeExprOrVector(pParse, pX->pRight, r1, 1);
        testcase( pX->op==TK_GT );
        testcase( pX->op==TK_GE );
        testcase( pX->op==TK_LT );
        testcase( pX->op==TK_LE );
        op = aMoveOp[((pX->op - TK_GT - 1) & 0x3) | 0x1];
        assert( pX->op!=TK_GT || op==OP_SeekGE );
        assert( pX->op!=TK_GE || op==OP_SeekGE );
        assert( pX->op!=TK_LT || op==OP_SeekLE );
        assert( pX->op!=TK_LE || op==OP_SeekLE );
      }else{
        r1 = sqlite3ExprCodeTemp(pParse, pX->pRight, &rTemp);
        disableTerm(pLevel, pStart);
        op = aMoveOp[(pX->op - TK_GT)];
      }
      sqlite3VdbeAddOp3(v, op, iCur, addrBrk, r1);
      VdbeComment((v, "pk"));
      VdbeCoverageIf(v, pX->op==TK_GT);
      VdbeCoverageIf(v, pX->op==TK_LE);
      VdbeCoverageIf(v, pX->op==TK_LT);
      VdbeCoverageIf(v, pX->op==TK_GE);
      sqlite3ReleaseTempReg(pParse, rTemp);
    }else{
      sqlite3VdbeAddOp2(v, bRev ? OP_Last : OP_Rewind, iCur, addrHalt);
      VdbeCoverageIf(v, bRev==0);
      VdbeCoverageIf(v, bRev!=0);
    }
    if( pEnd ){
      Expr *pX;
      pX = pEnd->pExpr;
      assert( pX!=0 );
      assert( (pEnd->wtFlags & TERM_VNULL)==0 );
      testcase( pEnd->leftCursor!=iCur );
      testcase( pEnd->wtFlags & TERM_VIRTUAL );
      memEndValue = ++pParse->nMem;
      codeExprOrVector(pParse, pX->pRight, memEndValue, 1);
      if( 0==sqlite3ExprIsVector(pX->pRight)
       && (pX->op==TK_LT || pX->op==TK_GT)
      ){
        testOp = bRev ? OP_Le : OP_Ge;
      }else{
        testOp = bRev ? OP_Lt : OP_Gt;
      }
      if( 0==sqlite3ExprIsVector(pX->pRight) ){
        disableTerm(pLevel, pEnd);
      }
    }
    start = sqlite3VdbeCurrentAddr(v);
    pLevel->op = bRev ? OP_Prev : OP_Next;
    pLevel->p1 = iCur;
    pLevel->p2 = start;
    assert( pLevel->p5==0 );
    if( testOp!=OP_Noop ){
      iRowidReg = ++pParse->nMem;
      sqlite3VdbeAddOp2(v, OP_Rowid, iCur, iRowidReg);
      sqlite3VdbeAddOp3(v, testOp, memEndValue, addrBrk, iRowidReg);
      VdbeCoverageIf(v, testOp==OP_Le);
      VdbeCoverageIf(v, testOp==OP_Lt);
      VdbeCoverageIf(v, testOp==OP_Ge);
      VdbeCoverageIf(v, testOp==OP_Gt);
      sqlite3VdbeChangeP5(v, SQLITE_AFF_NUMERIC | SQLITE_JUMPIFNULL);
    }
  }else if( pLoop->wsFlags & WHERE_INDEXED ){


    static const u8 aStartOp[] = {
      0,
      0,
      OP_Rewind,
      OP_Last,
      OP_SeekGT,
      OP_SeekLT,
      OP_SeekGE,
      OP_SeekLE
    };
    static const u8 aEndOp[] = {
      OP_IdxGE,
      OP_IdxGT,
      OP_IdxLE,
      OP_IdxLT,
    };
    u16 nEq = pLoop->u.btree.nEq;
    u16 nBtm = pLoop->u.btree.nBtm;
    u16 nTop = pLoop->u.btree.nTop;
    int regBase;
    WhereTerm *pRangeStart = 0;
    WhereTerm *pRangeEnd = 0;
    int startEq;
    int endEq;
    int start_constraints;
    int nConstraint;
    int iIdxCur;
    int nExtraReg = 0;
    int op;
    char *zStartAff;
    char *zEndAff = 0;
    u8 bSeekPastNull = 0;
    u8 bStopAtNull = 0;
    int omitTable;
    int regBignull = 0;

    pIdx = pLoop->u.btree.pIndex;
    iIdxCur = pLevel->iIdxCur;
    assert( nEq>=pLoop->nSkip );


    j = nEq;
    if( pLoop->wsFlags & WHERE_BTM_LIMIT ){
      pRangeStart = pLoop->aLTerm[j++];
      nExtraReg = MAX(nExtraReg, pLoop->u.btree.nBtm);

      assert( (pRangeStart->wtFlags & TERM_LIKEOPT)==0 ||
              (pLoop->wsFlags & WHERE_TOP_LIMIT)!=0 );
    }
    if( pLoop->wsFlags & WHERE_TOP_LIMIT ){
      pRangeEnd = pLoop->aLTerm[j++];
      nExtraReg = MAX(nExtraReg, pLoop->u.btree.nTop);
#ifndef SQLITE_LIKE_DOESNT_MATCH_BLOBS
      if( (pRangeEnd->wtFlags & TERM_LIKEOPT)!=0 ){
        assert( pRangeStart!=0 );
        assert( pRangeStart->wtFlags & TERM_LIKEOPT );
        pLevel->iLikeRepCntr = (u32)++pParse->nMem;
        sqlite3VdbeAddOp2(v, OP_Integer, 1, (int)pLevel->iLikeRepCntr);
        VdbeComment((v, "LIKE loop counter"));
        pLevel->addrLikeRep = sqlite3VdbeCurrentAddr(v);


        testcase( bRev );
        testcase( pIdx->aSortOrder[nEq]==SQLITE_SO_DESC );
        assert( (bRev & ~1)==0 );
        pLevel->iLikeRepCntr <<=1;
        pLevel->iLikeRepCntr |= bRev ^ (pIdx->aSortOrder[nEq]==SQLITE_SO_DESC);
      }
#endif
      if( pRangeStart==0 ){
        j = pIdx->aiColumn[nEq];
        if( (j>=0 && pIdx->pTable->aCol[j].notNull==0) || j==XN_EXPR ){
          bSeekPastNull = 1;
        }
      }
    }
    assert( pRangeEnd==0 || (pRangeEnd->wtFlags & TERM_VNULL)==0 );


    if( (pLoop->wsFlags & (WHERE_TOP_LIMIT|WHERE_BTM_LIMIT))==0
     && (pLoop->wsFlags & WHERE_BIGNULL_SORT)!=0
    ){
      assert( bSeekPastNull==0 && nExtraReg==0 && nBtm==0 && nTop==0 );
      assert( pRangeEnd==0 && pRangeStart==0 );
      assert( pLoop->nSkip==0 );
      nExtraReg = 1;
      bSeekPastNull = 1;
      pLevel->regBignull = regBignull = ++pParse->nMem;
      pLevel->addrBignull = sqlite3VdbeMakeLabel(pParse);
    }


    if( (nEq<pIdx->nKeyCol && bRev==(pIdx->aSortOrder[nEq]==SQLITE_SO_ASC))
     || (bRev && pIdx->nKeyCol==nEq)
    ){
      SWAP(WhereTerm *, pRangeEnd, pRangeStart);
      SWAP(u8, bSeekPastNull, bStopAtNull);
      SWAP(u8, nBtm, nTop);
    }


    codeCursorHint(pTabItem, pWInfo, pLevel, pRangeEnd);
    regBase = codeAllEqualityTerms(pParse,pLevel,bRev,nExtraReg,&zStartAff);
    assert( zStartAff==0 || sqlite3Strlen30(zStartAff)>=nEq );
    if( zStartAff && nTop ){
      zEndAff = sqlite3DbStrDup(db, &zStartAff[nEq]);
    }
    addrNxt = (regBignull ? pLevel->addrBignull : pLevel->addrNxt);

    testcase( pRangeStart && (pRangeStart->eOperator & WO_LE)!=0 );
    testcase( pRangeStart && (pRangeStart->eOperator & WO_GE)!=0 );
    testcase( pRangeEnd && (pRangeEnd->eOperator & WO_LE)!=0 );
    testcase( pRangeEnd && (pRangeEnd->eOperator & WO_GE)!=0 );
    startEq = !pRangeStart || pRangeStart->eOperator & (WO_LE|WO_GE);
    endEq =   !pRangeEnd || pRangeEnd->eOperator & (WO_LE|WO_GE);
    start_constraints = pRangeStart || nEq>0;


    nConstraint = nEq;
    if( pRangeStart ){
      Expr *pRight = pRangeStart->pExpr->pRight;
      codeExprOrVector(pParse, pRight, regBase+nEq, nBtm);
      whereLikeOptimizationStringFixup(v, pLevel, pRangeStart);
      if( (pRangeStart->wtFlags & TERM_VNULL)==0
       && sqlite3ExprCanBeNull(pRight)
      ){
        sqlite3VdbeAddOp2(v, OP_IsNull, regBase+nEq, addrNxt);
        VdbeCoverage(v);
      }
      if( zStartAff ){
        updateRangeAffinityStr(pRight, nBtm, &zStartAff[nEq]);
      }
      nConstraint += nBtm;
      testcase( pRangeStart->wtFlags & TERM_VIRTUAL );
      if( sqlite3ExprIsVector(pRight)==0 ){
        disableTerm(pLevel, pRangeStart);
      }else{
        startEq = 1;
      }
      bSeekPastNull = 0;
    }else if( bSeekPastNull ){
      startEq = 0;
      sqlite3VdbeAddOp2(v, OP_Null, 0, regBase+nEq);
      start_constraints = 1;
      nConstraint++;
    }else if( regBignull ){
      sqlite3VdbeAddOp2(v, OP_Null, 0, regBase+nEq);
      start_constraints = 1;
      nConstraint++;
    }
    codeApplyAffinity(pParse, regBase, nConstraint - bSeekPastNull, zStartAff);
    if( pLoop->nSkip>0 && nConstraint==pLoop->nSkip ){


    }else{
      if( pLoop->wsFlags & WHERE_IN_EARLYOUT ){
        sqlite3VdbeAddOp1(v, OP_SeekHit, iIdxCur);
      }
      if( regBignull ){
        sqlite3VdbeAddOp2(v, OP_Integer, 1, regBignull);
        VdbeComment((v, "NULL-scan pass ctr"));
      }

      op = aStartOp[(start_constraints<<2) + (startEq<<1) + bRev];
      assert( op!=0 );
      sqlite3VdbeAddOp4Int(v, op, iIdxCur, addrNxt, regBase, nConstraint);
      VdbeCoverage(v);
      VdbeCoverageIf(v, op==OP_Rewind);  testcase( op==OP_Rewind );
      VdbeCoverageIf(v, op==OP_Last);    testcase( op==OP_Last );
      VdbeCoverageIf(v, op==OP_SeekGT);  testcase( op==OP_SeekGT );
      VdbeCoverageIf(v, op==OP_SeekGE);  testcase( op==OP_SeekGE );
      VdbeCoverageIf(v, op==OP_SeekLE);  testcase( op==OP_SeekLE );
      VdbeCoverageIf(v, op==OP_SeekLT);  testcase( op==OP_SeekLT );

      assert( bSeekPastNull==0 || bStopAtNull==0 );
      if( regBignull ){
        assert( bSeekPastNull==1 || bStopAtNull==1 );
        assert( bSeekPastNull==!bStopAtNull );
        assert( bStopAtNull==startEq );
        sqlite3VdbeAddOp2(v, OP_Goto, 0, sqlite3VdbeCurrentAddr(v)+2);
        op = aStartOp[(nConstraint>1)*4 + 2 + bRev];
        sqlite3VdbeAddOp4Int(v, op, iIdxCur, addrNxt, regBase,
                             nConstraint-startEq);
        VdbeCoverage(v);
        VdbeCoverageIf(v, op==OP_Rewind);  testcase( op==OP_Rewind );
        VdbeCoverageIf(v, op==OP_Last);    testcase( op==OP_Last );
        VdbeCoverageIf(v, op==OP_SeekGE);  testcase( op==OP_SeekGE );
        VdbeCoverageIf(v, op==OP_SeekLE);  testcase( op==OP_SeekLE );
        assert( op==OP_Rewind || op==OP_Last || op==OP_SeekGE || op==OP_SeekLE);
      }
    }


    nConstraint = nEq;
    if( pRangeEnd ){
      Expr *pRight = pRangeEnd->pExpr->pRight;
      codeExprOrVector(pParse, pRight, regBase+nEq, nTop);
      whereLikeOptimizationStringFixup(v, pLevel, pRangeEnd);
      if( (pRangeEnd->wtFlags & TERM_VNULL)==0
       && sqlite3ExprCanBeNull(pRight)
      ){
        sqlite3VdbeAddOp2(v, OP_IsNull, regBase+nEq, addrNxt);
        VdbeCoverage(v);
      }
      if( zEndAff ){
        updateRangeAffinityStr(pRight, nTop, zEndAff);
        codeApplyAffinity(pParse, regBase+nEq, nTop, zEndAff);
      }else{
        assert( pParse->db->mallocFailed );
      }
      nConstraint += nTop;
      testcase( pRangeEnd->wtFlags & TERM_VIRTUAL );

      if( sqlite3ExprIsVector(pRight)==0 ){
        disableTerm(pLevel, pRangeEnd);
      }else{
        endEq = 1;
      }
    }else if( bStopAtNull ){
      if( regBignull==0 ){
        sqlite3VdbeAddOp2(v, OP_Null, 0, regBase+nEq);
        endEq = 0;
      }
      nConstraint++;
    }
    sqlite3DbFree(db, zStartAff);
    sqlite3DbFree(db, zEndAff);


    pLevel->p2 = sqlite3VdbeCurrentAddr(v);


    if( nConstraint ){
      if( regBignull ){

        sqlite3VdbeAddOp2(v, OP_IfNot, regBignull, sqlite3VdbeCurrentAddr(v)+3);
        VdbeComment((v, "If NULL-scan 2nd pass"));
        VdbeCoverage(v);
      }
      op = aEndOp[bRev*2 + endEq];
      sqlite3VdbeAddOp4Int(v, op, iIdxCur, addrNxt, regBase, nConstraint);
      testcase( op==OP_IdxGT );  VdbeCoverageIf(v, op==OP_IdxGT );
      testcase( op==OP_IdxGE );  VdbeCoverageIf(v, op==OP_IdxGE );
      testcase( op==OP_IdxLT );  VdbeCoverageIf(v, op==OP_IdxLT );
      testcase( op==OP_IdxLE );  VdbeCoverageIf(v, op==OP_IdxLE );
    }
    if( regBignull ){


      assert( bSeekPastNull==!bStopAtNull );
      assert( bSeekPastNull+bStopAtNull==1 );
      assert( nConstraint+bSeekPastNull>0 );
      sqlite3VdbeAddOp2(v, OP_If, regBignull, sqlite3VdbeCurrentAddr(v)+2);
      VdbeComment((v, "If NULL-scan 1st pass"));
      VdbeCoverage(v);
      op = aEndOp[bRev*2 + bSeekPastNull];
      sqlite3VdbeAddOp4Int(v, op, iIdxCur, addrNxt, regBase,
                           nConstraint+bSeekPastNull);
      testcase( op==OP_IdxGT );  VdbeCoverageIf(v, op==OP_IdxGT );
      testcase( op==OP_IdxGE );  VdbeCoverageIf(v, op==OP_IdxGE );
      testcase( op==OP_IdxLT );  VdbeCoverageIf(v, op==OP_IdxLT );
      testcase( op==OP_IdxLE );  VdbeCoverageIf(v, op==OP_IdxLE );
    }

    if( pLoop->wsFlags & WHERE_IN_EARLYOUT ){
      sqlite3VdbeAddOp2(v, OP_SeekHit, iIdxCur, 1);
    }


    omitTable = (pLoop->wsFlags & WHERE_IDX_ONLY)!=0
           && (pWInfo->wctrlFlags & WHERE_OR_SUBCLAUSE)==0;
    if( omitTable ){

    }else if( HasRowid(pIdx->pTable) ){
      if( (pWInfo->wctrlFlags & WHERE_SEEK_TABLE) || (
          (pWInfo->wctrlFlags & WHERE_SEEK_UNIQ_TABLE)
       && (pWInfo->eOnePass==ONEPASS_SINGLE)
      )){
        iRowidReg = ++pParse->nMem;
        sqlite3VdbeAddOp2(v, OP_IdxRowid, iIdxCur, iRowidReg);
        sqlite3VdbeAddOp3(v, OP_NotExists, iCur, 0, iRowidReg);
        VdbeCoverage(v);
      }else{
        codeDeferredSeek(pWInfo, pIdx, iCur, iIdxCur);
      }
    }else if( iCur!=iIdxCur ){
      Index *pPk = sqlite3PrimaryKeyIndex(pIdx->pTable);
      iRowidReg = sqlite3GetTempRange(pParse, pPk->nKeyCol);
      for(j=0; j<pPk->nKeyCol; j++){
        k = sqlite3TableColumnToIndex(pIdx, pPk->aiColumn[j]);
        sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, k, iRowidReg+j);
      }
      sqlite3VdbeAddOp4Int(v, OP_NotFound, iCur, addrCont,
                           iRowidReg, pPk->nKeyCol); VdbeCoverage(v);
    }

    if( pLevel->iLeftJoin==0 ){


      if( (pWInfo->wctrlFlags & WHERE_OR_SUBCLAUSE)==0 ){
        whereIndexExprTrans(pIdx, iCur, iIdxCur, pWInfo);
      }


      if( pIdx->pPartIdxWhere ){
        whereApplyPartialIndexConstraints(pIdx->pPartIdxWhere, iCur, pWC);
      }
    }else{
      testcase( pIdx->pPartIdxWhere );


      assert( (pWInfo->wctrlFlags & WHERE_OR_SUBCLAUSE)==0 );
    }


    if( pLoop->wsFlags & WHERE_ONEROW ){
      pLevel->op = OP_Noop;
    }else if( bRev ){
      pLevel->op = OP_Prev;
    }else{
      pLevel->op = OP_Next;
    }
    pLevel->p1 = iIdxCur;
    pLevel->p3 = (pLoop->wsFlags&WHERE_UNQ_WANTED)!=0 ? 1:0;
    if( (pLoop->wsFlags & WHERE_CONSTRAINT)==0 ){
      pLevel->p5 = SQLITE_STMTSTATUS_FULLSCAN_STEP;
    }else{
      assert( pLevel->p5==0 );
    }
    if( omitTable ) pIdx = 0;
  }else

#ifndef SQLITE_OMIT_OR_OPTIMIZATION
  if( pLoop->wsFlags & WHERE_MULTI_OR ){


    WhereClause *pOrWc;
    SrcList *pOrTab;
    Index *pCov = 0;
    int iCovCur = pParse->nTab++;

    int regReturn = ++pParse->nMem;
    int regRowset = 0;
    int regRowid = 0;
    int iLoopBody = sqlite3VdbeMakeLabel(pParse);
    int iRetInit;
    int untestedTerms = 0;
    int ii;
    u16 wctrlFlags;
    Expr *pAndExpr = 0;
    Table *pTab = pTabItem->pTab;

    pTerm = pLoop->aLTerm[0];
    assert( pTerm!=0 );
    assert( pTerm->eOperator & WO_OR );
    assert( (pTerm->wtFlags & TERM_ORINFO)!=0 );
    pOrWc = &pTerm->u.pOrInfo->wc;
    pLevel->op = OP_Return;
    pLevel->p1 = regReturn;


    if( pWInfo->nLevel>1 ){
      int nNotReady;
      struct SrcList_item *origSrc;
      nNotReady = pWInfo->nLevel - iLevel - 1;
      pOrTab = sqlite3StackAllocRaw(db,
                            sizeof(*pOrTab)+ nNotReady*sizeof(pOrTab->a[0]));
      if( pOrTab==0 ) return notReady;
      pOrTab->nAlloc = (u8)(nNotReady + 1);
      pOrTab->nSrc = pOrTab->nAlloc;
      memcpy(pOrTab->a, pTabItem, sizeof(*pTabItem));
      origSrc = pWInfo->pTabList->a;
      for(k=1; k<=nNotReady; k++){
        memcpy(&pOrTab->a[k], &origSrc[pLevel[k].iFrom], sizeof(pOrTab->a[k]));
      }
    }else{
      pOrTab = pWInfo->pTabList;
    }


    if( (pWInfo->wctrlFlags & WHERE_DUPLICATES_OK)==0 ){
      if( HasRowid(pTab) ){
        regRowset = ++pParse->nMem;
        sqlite3VdbeAddOp2(v, OP_Null, 0, regRowset);
      }else{
        Index *pPk = sqlite3PrimaryKeyIndex(pTab);
        regRowset = pParse->nTab++;
        sqlite3VdbeAddOp2(v, OP_OpenEphemeral, regRowset, pPk->nKeyCol);
        sqlite3VdbeSetP4KeyInfo(pParse, pPk);
      }
      regRowid = ++pParse->nMem;
    }
    iRetInit = sqlite3VdbeAddOp2(v, OP_Integer, 0, regReturn);


    if( pWC->nTerm>1 ){
      int iTerm;
      for(iTerm=0; iTerm<pWC->nTerm; iTerm++){
        Expr *pExpr = pWC->a[iTerm].pExpr;
        if( &pWC->a[iTerm] == pTerm ) continue;
        testcase( pWC->a[iTerm].wtFlags & TERM_VIRTUAL );
        testcase( pWC->a[iTerm].wtFlags & TERM_CODED );
        if( (pWC->a[iTerm].wtFlags & (TERM_VIRTUAL|TERM_CODED))!=0 ) continue;
        if( (pWC->a[iTerm].eOperator & WO_ALL)==0 ) continue;
        testcase( pWC->a[iTerm].wtFlags & TERM_ORINFO );
        pExpr = sqlite3ExprDup(db, pExpr, 0);
        pAndExpr = sqlite3ExprAnd(pParse, pAndExpr, pExpr);
      }
      if( pAndExpr ){


        pAndExpr = sqlite3PExpr(pParse, TK_AND|0x10000, 0, pAndExpr);
      }
    }


    wctrlFlags =  WHERE_OR_SUBCLAUSE | (pWInfo->wctrlFlags & WHERE_SEEK_TABLE);
    ExplainQueryPlan((pParse, 1, "MULTI-INDEX OR"));
    for(ii=0; ii<pOrWc->nTerm; ii++){
      WhereTerm *pOrTerm = &pOrWc->a[ii];
      if( pOrTerm->leftCursor==iCur || (pOrTerm->eOperator & WO_AND)!=0 ){
        WhereInfo *pSubWInfo;
        Expr *pOrExpr = pOrTerm->pExpr;
        int jmp1 = 0;
        assert( (pTabItem[0].fg.jointype & JT_LEFT)==0
             || ExprHasProperty(pOrExpr, EP_FromJoin)
        );
        if( pAndExpr ){
          pAndExpr->pLeft = pOrExpr;
          pOrExpr = pAndExpr;
        }

        ExplainQueryPlan((pParse, 1, "INDEX %d", ii+1));
        WHERETRACE(0xffff, ("Subplan for OR-clause:\n"));
        pSubWInfo = sqlite3WhereBegin(pParse, pOrTab, pOrExpr, 0, 0,
                                      wctrlFlags, iCovCur);
        assert( pSubWInfo || pParse->nErr || db->mallocFailed );
        if( pSubWInfo ){
          WhereLoop *pSubLoop;
          int addrExplain = sqlite3WhereExplainOneScan(
              pParse, pOrTab, &pSubWInfo->a[0], 0
          );
          sqlite3WhereAddScanStatus(v, pOrTab, &pSubWInfo->a[0], addrExplain);


          if( (pWInfo->wctrlFlags & WHERE_DUPLICATES_OK)==0 ){
            int iSet = ((ii==pOrWc->nTerm-1)?-1:ii);
            if( HasRowid(pTab) ){
              sqlite3ExprCodeGetColumnOfTable(v, pTab, iCur, -1, regRowid);
              jmp1 = sqlite3VdbeAddOp4Int(v, OP_RowSetTest, regRowset, 0,
                                          regRowid, iSet);
              VdbeCoverage(v);
            }else{
              Index *pPk = sqlite3PrimaryKeyIndex(pTab);
              int nPk = pPk->nKeyCol;
              int iPk;
              int r;


              r = sqlite3GetTempRange(pParse, nPk);
              for(iPk=0; iPk<nPk; iPk++){
                int iCol = pPk->aiColumn[iPk];
                sqlite3ExprCodeGetColumnOfTable(v, pTab, iCur, iCol,r+iPk);
              }


              if( iSet ){
                jmp1 = sqlite3VdbeAddOp4Int(v, OP_Found, regRowset, 0, r, nPk);
                VdbeCoverage(v);
              }
              if( iSet>=0 ){
                sqlite3VdbeAddOp3(v, OP_MakeRecord, r, nPk, regRowid);
                sqlite3VdbeAddOp4Int(v, OP_IdxInsert, regRowset, regRowid,
                                     r, nPk);
                if( iSet ) sqlite3VdbeChangeP5(v, OPFLAG_USESEEKRESULT);
              }


              sqlite3ReleaseTempRange(pParse, r, nPk);
            }
          }


          sqlite3VdbeAddOp2(v, OP_Gosub, regReturn, iLoopBody);


          if( jmp1 ) sqlite3VdbeJumpHere(v, jmp1);


          if( pSubWInfo->untestedTerms ) untestedTerms = 1;


          pSubLoop = pSubWInfo->a[0].pWLoop;
          assert( (pSubLoop->wsFlags & WHERE_AUTO_INDEX)==0 );
          if( (pSubLoop->wsFlags & WHERE_INDEXED)!=0
           && (ii==0 || pSubLoop->u.btree.pIndex==pCov)
           && (HasRowid(pTab) || !IsPrimaryKeyIndex(pSubLoop->u.btree.pIndex))
          ){
            assert( pSubWInfo->a[0].iIdxCur==iCovCur );
            pCov = pSubLoop->u.btree.pIndex;
          }else{
            pCov = 0;
          }


          sqlite3WhereEnd(pSubWInfo);
          ExplainQueryPlanPop(pParse);
        }
      }
    }
    ExplainQueryPlanPop(pParse);
    pLevel->u.pCovidx = pCov;
    if( pCov ) pLevel->iIdxCur = iCovCur;
    if( pAndExpr ){
      pAndExpr->pLeft = 0;
      sqlite3ExprDelete(db, pAndExpr);
    }
    sqlite3VdbeChangeP1(v, iRetInit, sqlite3VdbeCurrentAddr(v));
    sqlite3VdbeGoto(v, pLevel->addrBrk);
    sqlite3VdbeResolveLabel(v, iLoopBody);

    if( pWInfo->nLevel>1 ){ sqlite3StackFree(db, pOrTab); }
    if( !untestedTerms ) disableTerm(pLevel, pTerm);
  }else
#endif

  {


    static const u8 aStep[] = { OP_Next, OP_Prev };
    static const u8 aStart[] = { OP_Rewind, OP_Last };
    assert( bRev==0 || bRev==1 );
    if( pTabItem->fg.isRecursive ){


      pLevel->op = OP_Noop;
    }else{
      codeCursorHint(pTabItem, pWInfo, pLevel, 0);
      pLevel->op = aStep[bRev];
      pLevel->p1 = iCur;
      pLevel->p2 = 1 + sqlite3VdbeAddOp2(v, aStart[bRev], iCur, addrHalt);
      VdbeCoverageIf(v, bRev==0);
      VdbeCoverageIf(v, bRev!=0);
      pLevel->p5 = SQLITE_STMTSTATUS_FULLSCAN_STEP;
    }
  }

#ifdef SQLITE_ENABLE_STMT_SCANSTATUS
  pLevel->addrVisit = sqlite3VdbeCurrentAddr(v);
#endif


  iLoop = (pIdx ? 1 : 2);
  do{
    int iNext = 0;
    for(pTerm=pWC->a, j=pWC->nTerm; j>0; j--, pTerm++){
      Expr *pE;
      int skipLikeAddr = 0;
      testcase( pTerm->wtFlags & TERM_VIRTUAL );
      testcase( pTerm->wtFlags & TERM_CODED );
      if( pTerm->wtFlags & (TERM_VIRTUAL|TERM_CODED) ) continue;
      if( (pTerm->prereqAll & pLevel->notReady)!=0 ){
        testcase( pWInfo->untestedTerms==0
            && (pWInfo->wctrlFlags & WHERE_OR_SUBCLAUSE)!=0 );
        pWInfo->untestedTerms = 1;
        continue;
      }
      pE = pTerm->pExpr;
      assert( pE!=0 );
      if( (pTabItem->fg.jointype&JT_LEFT) && !ExprHasProperty(pE,EP_FromJoin) ){
        continue;
      }

      if( iLoop==1 && !sqlite3ExprCoveredByIndex(pE, pLevel->iTabCur, pIdx) ){
        iNext = 2;
        continue;
      }
      if( iLoop<3 && (pTerm->wtFlags & TERM_VARSELECT) ){
        if( iNext==0 ) iNext = 3;
        continue;
      }

      if( (pTerm->wtFlags & TERM_LIKECOND)!=0 ){


#ifdef SQLITE_LIKE_DOESNT_MATCH_BLOBS
        continue;
#else
        u32 x = pLevel->iLikeRepCntr;
        if( x>0 ){
          skipLikeAddr = sqlite3VdbeAddOp1(v, (x&1)?OP_IfNot:OP_If,(int)(x>>1));
          VdbeCoverageIf(v, (x&1)==1);
          VdbeCoverageIf(v, (x&1)==0);
        }
#endif
      }
#ifdef WHERETRACE_ENABLED
      if( sqlite3WhereTrace ){
        VdbeNoopComment((v, "WhereTerm[%d] (%p) priority=%d",
                         pWC->nTerm-j, pTerm, iLoop));
      }
#endif
      sqlite3ExprIfFalse(pParse, pE, addrCont, SQLITE_JUMPIFNULL);
      if( skipLikeAddr ) sqlite3VdbeJumpHere(v, skipLikeAddr);
      pTerm->wtFlags |= TERM_CODED;
    }
    iLoop = iNext;
  }while( iLoop>0 );


  for(pTerm=pWC->a, j=pWC->nTerm; j>0; j--, pTerm++){
    Expr *pE, sEAlt;
    WhereTerm *pAlt;
    if( pTerm->wtFlags & (TERM_VIRTUAL|TERM_CODED) ) continue;
    if( (pTerm->eOperator & (WO_EQ|WO_IS))==0 ) continue;
    if( (pTerm->eOperator & WO_EQUIV)==0 ) continue;
    if( pTerm->leftCursor!=iCur ) continue;
    if( pLevel->iLeftJoin ) continue;
    pE = pTerm->pExpr;
    assert( !ExprHasProperty(pE, EP_FromJoin) );
    assert( (pTerm->prereqRight & pLevel->notReady)!=0 );
    pAlt = sqlite3WhereFindTerm(pWC, iCur, pTerm->u.leftColumn, notReady,
                    WO_EQ|WO_IN|WO_IS, 0);
    if( pAlt==0 ) continue;
    if( pAlt->wtFlags & (TERM_CODED) ) continue;
    if( (pAlt->eOperator & WO_IN)
     && (pAlt->pExpr->flags & EP_xIsSelect)
     && (pAlt->pExpr->x.pSelect->pEList->nExpr>1)
    ){
      continue;
    }
    testcase( pAlt->eOperator & WO_EQ );
    testcase( pAlt->eOperator & WO_IS );
    testcase( pAlt->eOperator & WO_IN );
    VdbeModuleComment((v, "begin transitive constraint"));
    sEAlt = *pAlt->pExpr;
    sEAlt.pLeft = pE->pLeft;
    sqlite3ExprIfFalse(pParse, &sEAlt, addrCont, SQLITE_JUMPIFNULL);
  }


  if( pLevel->iLeftJoin ){
    pLevel->addrFirst = sqlite3VdbeCurrentAddr(v);
    sqlite3VdbeAddOp2(v, OP_Integer, 1, pLevel->iLeftJoin);
    VdbeComment((v, "record LEFT JOIN hit"));
    for(pTerm=pWC->a, j=0; j<pWC->nTerm; j++, pTerm++){
      testcase( pTerm->wtFlags & TERM_VIRTUAL );
      testcase( pTerm->wtFlags & TERM_CODED );
      if( pTerm->wtFlags & (TERM_VIRTUAL|TERM_CODED) ) continue;
      if( (pTerm->prereqAll & pLevel->notReady)!=0 ){
        assert( pWInfo->untestedTerms );
        continue;
      }
      assert( pTerm->pExpr );
      sqlite3ExprIfFalse(pParse, pTerm->pExpr, addrCont, SQLITE_JUMPIFNULL);
      pTerm->wtFlags |= TERM_CODED;
    }
  }

  return pLevel->notReady;
}
