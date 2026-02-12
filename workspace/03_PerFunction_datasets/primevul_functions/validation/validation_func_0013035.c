void sqlite3WindowCodeStep(
  Parse *pParse,
  Select *p,
  WhereInfo *pWInfo,
  int regGosub,
  int addrGosub
){
  Window *pMWin = p->pWin;
  ExprList *pOrderBy = pMWin->pOrderBy;
  Vdbe *v = sqlite3GetVdbe(pParse);
  int csrWrite;
  int csrInput = p->pSrc->a[0].iCursor;
  int nInput = p->pSrc->a[0].pTab->nCol;
  int iInput;
  int addrNe;
  int addrGosubFlush = 0;
  int addrInteger = 0;
  int addrEmpty;
  int regNew;
  int regRecord;
  int regRowid;
  int regNewPeer = 0;
  int regPeer = 0;
  int regFlushPart = 0;
  WindowCodeArg s;
  int lblWhereEnd;
  int regStart = 0;
  int regEnd = 0;

  assert( pMWin->eStart==TK_PRECEDING || pMWin->eStart==TK_CURRENT
       || pMWin->eStart==TK_FOLLOWING || pMWin->eStart==TK_UNBOUNDED
  );
  assert( pMWin->eEnd==TK_FOLLOWING || pMWin->eEnd==TK_CURRENT
       || pMWin->eEnd==TK_UNBOUNDED || pMWin->eEnd==TK_PRECEDING
  );
  assert( pMWin->eExclude==0 || pMWin->eExclude==TK_CURRENT
       || pMWin->eExclude==TK_GROUP || pMWin->eExclude==TK_TIES
       || pMWin->eExclude==TK_NO
  );

  lblWhereEnd = sqlite3VdbeMakeLabel(pParse);


  memset(&s, 0, sizeof(WindowCodeArg));
  s.pParse = pParse;
  s.pMWin = pMWin;
  s.pVdbe = v;
  s.regGosub = regGosub;
  s.addrGosub = addrGosub;
  s.current.csr = pMWin->iEphCsr;
  csrWrite = s.current.csr+1;
  s.start.csr = s.current.csr+2;
  s.end.csr = s.current.csr+3;


  switch( pMWin->eStart ){
    case TK_FOLLOWING:
      if( pMWin->eFrmType!=TK_RANGE
       && windowExprGtZero(pParse, pMWin->pStart)
      ){
        s.eDelete = WINDOW_RETURN_ROW;
      }
      break;
    case TK_UNBOUNDED:
      if( windowCacheFrame(pMWin)==0 ){
        if( pMWin->eEnd==TK_PRECEDING ){
          if( pMWin->eFrmType!=TK_RANGE
           && windowExprGtZero(pParse, pMWin->pEnd)
          ){
            s.eDelete = WINDOW_AGGSTEP;
          }
        }else{
          s.eDelete = WINDOW_RETURN_ROW;
        }
      }
      break;
    default:
      s.eDelete = WINDOW_AGGINVERSE;
      break;
  }


  regNew = pParse->nMem+1;
  pParse->nMem += nInput;
  regRecord = ++pParse->nMem;
  regRowid = ++pParse->nMem;


  if( pMWin->eStart==TK_PRECEDING || pMWin->eStart==TK_FOLLOWING ){
    regStart = ++pParse->nMem;
  }
  if( pMWin->eEnd==TK_PRECEDING || pMWin->eEnd==TK_FOLLOWING ){
    regEnd = ++pParse->nMem;
  }


  if( pMWin->eFrmType!=TK_ROWS ){
    int nPeer = (pOrderBy ? pOrderBy->nExpr : 0);
    regNewPeer = regNew + pMWin->nBufferCol;
    if( pMWin->pPartition ) regNewPeer += pMWin->pPartition->nExpr;
    regPeer = pParse->nMem+1;       pParse->nMem += nPeer;
    s.start.reg = pParse->nMem+1;   pParse->nMem += nPeer;
    s.current.reg = pParse->nMem+1; pParse->nMem += nPeer;
    s.end.reg = pParse->nMem+1;     pParse->nMem += nPeer;
  }


  for(iInput=0; iInput<nInput; iInput++){
    sqlite3VdbeAddOp3(v, OP_Column, csrInput, iInput, regNew+iInput);
  }
  sqlite3VdbeAddOp3(v, OP_MakeRecord, regNew, nInput, regRecord);


  if( pMWin->pPartition ){
    int addr;
    ExprList *pPart = pMWin->pPartition;
    int nPart = pPart->nExpr;
    int regNewPart = regNew + pMWin->nBufferCol;
    KeyInfo *pKeyInfo = sqlite3KeyInfoFromExprList(pParse, pPart, 0, 0);

    regFlushPart = ++pParse->nMem;
    addr = sqlite3VdbeAddOp3(v, OP_Compare, regNewPart, pMWin->regPart, nPart);
    sqlite3VdbeAppendP4(v, (void*)pKeyInfo, P4_KEYINFO);
    sqlite3VdbeAddOp3(v, OP_Jump, addr+2, addr+4, addr+2);
    VdbeCoverageEqNe(v);
    addrGosubFlush = sqlite3VdbeAddOp1(v, OP_Gosub, regFlushPart);
    VdbeComment((v, "call flush_partition"));
    sqlite3VdbeAddOp3(v, OP_Copy, regNewPart, pMWin->regPart, nPart-1);
  }


  sqlite3VdbeAddOp2(v, OP_NewRowid, csrWrite, regRowid);
  sqlite3VdbeAddOp3(v, OP_Insert, csrWrite, regRecord, regRowid);
  addrNe = sqlite3VdbeAddOp3(v, OP_Ne, pMWin->regOne, 0, regRowid);
  VdbeCoverageNeverNull(v);


  s.regArg = windowInitAccum(pParse, pMWin);

  if( regStart ){
    sqlite3ExprCode(pParse, pMWin->pStart, regStart);
    windowCheckValue(pParse, regStart, 0 + (pMWin->eFrmType==TK_RANGE?3:0));
  }
  if( regEnd ){
    sqlite3ExprCode(pParse, pMWin->pEnd, regEnd);
    windowCheckValue(pParse, regEnd, 1 + (pMWin->eFrmType==TK_RANGE?3:0));
  }

  if( pMWin->eFrmType!=TK_RANGE && pMWin->eStart==pMWin->eEnd && regStart ){
    int op = ((pMWin->eStart==TK_FOLLOWING) ? OP_Ge : OP_Le);
    int addrGe = sqlite3VdbeAddOp3(v, op, regStart, 0, regEnd);
    VdbeCoverageNeverNullIf(v, op==OP_Ge);
    VdbeCoverageNeverNullIf(v, op==OP_Le);
    windowAggFinal(&s, 0);
    sqlite3VdbeAddOp2(v, OP_Rewind, s.current.csr, 1);
    VdbeCoverageNeverTaken(v);
    windowReturnOneRow(&s);
    sqlite3VdbeAddOp1(v, OP_ResetSorter, s.current.csr);
    sqlite3VdbeAddOp2(v, OP_Goto, 0, lblWhereEnd);
    sqlite3VdbeJumpHere(v, addrGe);
  }
  if( pMWin->eStart==TK_FOLLOWING && pMWin->eFrmType!=TK_RANGE && regEnd ){
    assert( pMWin->eEnd==TK_FOLLOWING );
    sqlite3VdbeAddOp3(v, OP_Subtract, regStart, regEnd, regStart);
  }

  if( pMWin->eStart!=TK_UNBOUNDED ){
    sqlite3VdbeAddOp2(v, OP_Rewind, s.start.csr, 1);
    VdbeCoverageNeverTaken(v);
  }
  sqlite3VdbeAddOp2(v, OP_Rewind, s.current.csr, 1);
  VdbeCoverageNeverTaken(v);
  sqlite3VdbeAddOp2(v, OP_Rewind, s.end.csr, 1);
  VdbeCoverageNeverTaken(v);
  if( regPeer && pOrderBy ){
    sqlite3VdbeAddOp3(v, OP_Copy, regNewPeer, regPeer, pOrderBy->nExpr-1);
    sqlite3VdbeAddOp3(v, OP_Copy, regPeer, s.start.reg, pOrderBy->nExpr-1);
    sqlite3VdbeAddOp3(v, OP_Copy, regPeer, s.current.reg, pOrderBy->nExpr-1);
    sqlite3VdbeAddOp3(v, OP_Copy, regPeer, s.end.reg, pOrderBy->nExpr-1);
  }

  sqlite3VdbeAddOp2(v, OP_Goto, 0, lblWhereEnd);

  sqlite3VdbeJumpHere(v, addrNe);


  if( regPeer ){
    windowIfNewPeer(pParse, pOrderBy, regNewPeer, regPeer, lblWhereEnd);
  }
  if( pMWin->eStart==TK_FOLLOWING ){
    windowCodeOp(&s, WINDOW_AGGSTEP, 0, 0);
    if( pMWin->eEnd!=TK_UNBOUNDED ){
      if( pMWin->eFrmType==TK_RANGE ){
        int lbl = sqlite3VdbeMakeLabel(pParse);
        int addrNext = sqlite3VdbeCurrentAddr(v);
        windowCodeRangeTest(&s, OP_Ge, s.current.csr, regEnd, s.end.csr, lbl);
        windowCodeOp(&s, WINDOW_AGGINVERSE, regStart, 0);
        windowCodeOp(&s, WINDOW_RETURN_ROW, 0, 0);
        sqlite3VdbeAddOp2(v, OP_Goto, 0, addrNext);
        sqlite3VdbeResolveLabel(v, lbl);
      }else{
        windowCodeOp(&s, WINDOW_RETURN_ROW, regEnd, 0);
        windowCodeOp(&s, WINDOW_AGGINVERSE, regStart, 0);
      }
    }
  }else
  if( pMWin->eEnd==TK_PRECEDING ){
    int bRPS = (pMWin->eStart==TK_PRECEDING && pMWin->eFrmType==TK_RANGE);
    windowCodeOp(&s, WINDOW_AGGSTEP, regEnd, 0);
    if( bRPS ) windowCodeOp(&s, WINDOW_AGGINVERSE, regStart, 0);
    windowCodeOp(&s, WINDOW_RETURN_ROW, 0, 0);
    if( !bRPS ) windowCodeOp(&s, WINDOW_AGGINVERSE, regStart, 0);
  }else{
    int addr = 0;
    windowCodeOp(&s, WINDOW_AGGSTEP, 0, 0);
    if( pMWin->eEnd!=TK_UNBOUNDED ){
      if( pMWin->eFrmType==TK_RANGE ){
        int lbl = 0;
        addr = sqlite3VdbeCurrentAddr(v);
        if( regEnd ){
          lbl = sqlite3VdbeMakeLabel(pParse);
          windowCodeRangeTest(&s, OP_Ge, s.current.csr, regEnd, s.end.csr, lbl);
        }
        windowCodeOp(&s, WINDOW_RETURN_ROW, 0, 0);
        windowCodeOp(&s, WINDOW_AGGINVERSE, regStart, 0);
        if( regEnd ){
          sqlite3VdbeAddOp2(v, OP_Goto, 0, addr);
          sqlite3VdbeResolveLabel(v, lbl);
        }
      }else{
        if( regEnd ){
          addr = sqlite3VdbeAddOp3(v, OP_IfPos, regEnd, 0, 1);
          VdbeCoverage(v);
        }
        windowCodeOp(&s, WINDOW_RETURN_ROW, 0, 0);
        windowCodeOp(&s, WINDOW_AGGINVERSE, regStart, 0);
        if( regEnd ) sqlite3VdbeJumpHere(v, addr);
      }
    }
  }


  sqlite3VdbeResolveLabel(v, lblWhereEnd);
  sqlite3WhereEnd(pWInfo);


  if( pMWin->pPartition ){
    addrInteger = sqlite3VdbeAddOp2(v, OP_Integer, 0, regFlushPart);
    sqlite3VdbeJumpHere(v, addrGosubFlush);
  }

  addrEmpty = sqlite3VdbeAddOp1(v, OP_Rewind, csrWrite);
  VdbeCoverage(v);
  if( pMWin->eEnd==TK_PRECEDING ){
    int bRPS = (pMWin->eStart==TK_PRECEDING && pMWin->eFrmType==TK_RANGE);
    windowCodeOp(&s, WINDOW_AGGSTEP, regEnd, 0);
    if( bRPS ) windowCodeOp(&s, WINDOW_AGGINVERSE, regStart, 0);
    windowCodeOp(&s, WINDOW_RETURN_ROW, 0, 0);
  }else if( pMWin->eStart==TK_FOLLOWING ){
    int addrStart;
    int addrBreak1;
    int addrBreak2;
    int addrBreak3;
    windowCodeOp(&s, WINDOW_AGGSTEP, 0, 0);
    if( pMWin->eFrmType==TK_RANGE ){
      addrStart = sqlite3VdbeCurrentAddr(v);
      addrBreak2 = windowCodeOp(&s, WINDOW_AGGINVERSE, regStart, 1);
      addrBreak1 = windowCodeOp(&s, WINDOW_RETURN_ROW, 0, 1);
    }else
    if( pMWin->eEnd==TK_UNBOUNDED ){
      addrStart = sqlite3VdbeCurrentAddr(v);
      addrBreak1 = windowCodeOp(&s, WINDOW_RETURN_ROW, regStart, 1);
      addrBreak2 = windowCodeOp(&s, WINDOW_AGGINVERSE, 0, 1);
    }else{
      assert( pMWin->eEnd==TK_FOLLOWING );
      addrStart = sqlite3VdbeCurrentAddr(v);
      addrBreak1 = windowCodeOp(&s, WINDOW_RETURN_ROW, regEnd, 1);
      addrBreak2 = windowCodeOp(&s, WINDOW_AGGINVERSE, regStart, 1);
    }
    sqlite3VdbeAddOp2(v, OP_Goto, 0, addrStart);
    sqlite3VdbeJumpHere(v, addrBreak2);
    addrStart = sqlite3VdbeCurrentAddr(v);
    addrBreak3 = windowCodeOp(&s, WINDOW_RETURN_ROW, 0, 1);
    sqlite3VdbeAddOp2(v, OP_Goto, 0, addrStart);
    sqlite3VdbeJumpHere(v, addrBreak1);
    sqlite3VdbeJumpHere(v, addrBreak3);
  }else{
    int addrBreak;
    int addrStart;
    windowCodeOp(&s, WINDOW_AGGSTEP, 0, 0);
    addrStart = sqlite3VdbeCurrentAddr(v);
    addrBreak = windowCodeOp(&s, WINDOW_RETURN_ROW, 0, 1);
    windowCodeOp(&s, WINDOW_AGGINVERSE, regStart, 0);
    sqlite3VdbeAddOp2(v, OP_Goto, 0, addrStart);
    sqlite3VdbeJumpHere(v, addrBreak);
  }
  sqlite3VdbeJumpHere(v, addrEmpty);

  sqlite3VdbeAddOp1(v, OP_ResetSorter, s.current.csr);
  if( pMWin->pPartition ){
    if( pMWin->regStartRowid ){
      sqlite3VdbeAddOp2(v, OP_Integer, 1, pMWin->regStartRowid);
      sqlite3VdbeAddOp2(v, OP_Integer, 0, pMWin->regEndRowid);
    }
    sqlite3VdbeChangeP1(v, addrInteger, sqlite3VdbeCurrentAddr(v));
    sqlite3VdbeAddOp1(v, OP_Return, regFlushPart);
  }
}
