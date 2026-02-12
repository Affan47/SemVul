int sqlite3Select(
  Parse *pParse,
  Select *p,
  SelectDest *pDest
){
  int i, j;
  WhereInfo *pWInfo;
  Vdbe *v;
  int isAgg;
  ExprList *pEList = 0;
  SrcList *pTabList;
  Expr *pWhere;
  ExprList *pGroupBy;
  Expr *pHaving;
  int rc = 1;
  DistinctCtx sDistinct;
  SortCtx sSort;
  AggInfo sAggInfo;
  int iEnd;
  sqlite3 *db;
  ExprList *pMinMaxOrderBy = 0;
  u8 minMaxFlag;

  db = pParse->db;
  v = sqlite3GetVdbe(pParse);
  if( p==0 || db->mallocFailed || pParse->nErr ){
    return 1;
  }
  if( sqlite3AuthCheck(pParse, SQLITE_SELECT, 0, 0, 0) ) return 1;
  memset(&sAggInfo, 0, sizeof(sAggInfo));
#if SELECTTRACE_ENABLED
  SELECTTRACE(1,pParse,p, ("begin processing:\n", pParse->addrExplain));
  if( sqlite3SelectTrace & 0x100 ){
    sqlite3TreeViewSelect(0, p, 0);
  }
#endif

  assert( p->pOrderBy==0 || pDest->eDest!=SRT_DistFifo );
  assert( p->pOrderBy==0 || pDest->eDest!=SRT_Fifo );
  assert( p->pOrderBy==0 || pDest->eDest!=SRT_DistQueue );
  assert( p->pOrderBy==0 || pDest->eDest!=SRT_Queue );
  if( IgnorableOrderby(pDest) ){
    assert(pDest->eDest==SRT_Exists || pDest->eDest==SRT_Union ||
           pDest->eDest==SRT_Except || pDest->eDest==SRT_Discard ||
           pDest->eDest==SRT_Queue  || pDest->eDest==SRT_DistFifo ||
           pDest->eDest==SRT_DistQueue || pDest->eDest==SRT_Fifo);


    sqlite3ExprListDelete(db, p->pOrderBy);
    p->pOrderBy = 0;
    p->selFlags &= ~SF_Distinct;
  }
  sqlite3SelectPrep(pParse, p, 0);
  if( pParse->nErr || db->mallocFailed ){
    goto select_end;
  }
  assert( p->pEList!=0 );
#if SELECTTRACE_ENABLED
  if( sqlite3SelectTrace & 0x104 ){
    SELECTTRACE(0x104,pParse,p, ("after name resolution:\n"));
    sqlite3TreeViewSelect(0, p, 0);
  }
#endif

  if( pDest->eDest==SRT_Output ){
    generateColumnNames(pParse, p);
  }

#ifndef SQLITE_OMIT_WINDOWFUNC
  if( sqlite3WindowRewrite(pParse, p) ){
    goto select_end;
  }
#if SELECTTRACE_ENABLED
  if( p->pWin && (sqlite3SelectTrace & 0x108)!=0 ){
    SELECTTRACE(0x104,pParse,p, ("after window rewrite:\n"));
    sqlite3TreeViewSelect(0, p, 0);
  }
#endif
#endif
  pTabList = p->pSrc;
  isAgg = (p->selFlags & SF_Aggregate)!=0;
  memset(&sSort, 0, sizeof(sSort));
  sSort.pOrderBy = p->pOrderBy;


#if !defined(SQLITE_OMIT_SUBQUERY) || !defined(SQLITE_OMIT_VIEW)
  for(i=0; !p->pPrior && i<pTabList->nSrc; i++){
    struct SrcList_item *pItem = &pTabList->a[i];
    Select *pSub = pItem->pSelect;
    Table *pTab = pItem->pTab;


    if( (pItem->fg.jointype & JT_LEFT)!=0
     && sqlite3ExprImpliesNonNullRow(p->pWhere, pItem->iCursor)
     && OptimizationEnabled(db, SQLITE_SimplifyJoin)
    ){
      SELECTTRACE(0x100,pParse,p,
                ("LEFT-JOIN simplifies to JOIN on term %d\n",i));
      pItem->fg.jointype &= ~(JT_LEFT|JT_OUTER);
      unsetJoinExpr(p->pWhere, pItem->iCursor);
    }


    if( pSub==0 ) continue;


    if( pTab->nCol!=pSub->pEList->nExpr ){
      sqlite3ErrorMsg(pParse, "expected %d columns for '%s' but got %d",
                      pTab->nCol, pTab->zName, pSub->pEList->nExpr);
      goto select_end;
    }


    if( (pSub->selFlags & SF_Aggregate)!=0 ) continue;
    assert( pSub->pGroupBy==0 );


    if( pSub->pOrderBy!=0
     && i==0
     && (p->selFlags & SF_ComplexResult)!=0
     && (pTabList->nSrc==1
         || (pTabList->a[1].fg.jointype&(JT_LEFT|JT_CROSS))!=0)
    ){
      continue;
    }

    if( flattenSubquery(pParse, p, i, isAgg) ){
      if( pParse->nErr ) goto select_end;

      i = -1;
    }
    pTabList = p->pSrc;
    if( db->mallocFailed ) goto select_end;
    if( !IgnorableOrderby(pDest) ){
      sSort.pOrderBy = p->pOrderBy;
    }
  }
#endif

#ifndef SQLITE_OMIT_COMPOUND_SELECT


  if( p->pPrior ){
    rc = multiSelect(pParse, p, pDest);
#if SELECTTRACE_ENABLED
    SELECTTRACE(0x1,pParse,p,("end compound-select processing\n"));
    if( (sqlite3SelectTrace & 0x2000)!=0 && ExplainQueryPlanParent(pParse)==0 ){
      sqlite3TreeViewSelect(0, p, 0);
    }
#endif
    if( p->pNext==0 ) ExplainQueryPlanPop(pParse);
    return rc;
  }
#endif


  if( pTabList->nSrc>1
   && OptimizationEnabled(db, SQLITE_PropagateConst)
   && propagateConstants(pParse, p)
  ){
#if SELECTTRACE_ENABLED
    if( sqlite3SelectTrace & 0x100 ){
      SELECTTRACE(0x100,pParse,p,("After constant propagation:\n"));
      sqlite3TreeViewSelect(0, p, 0);
    }
#endif
  }else{
    SELECTTRACE(0x100,pParse,p,("Constant propagation not helpful\n"));
  }

#ifdef SQLITE_COUNTOFVIEW_OPTIMIZATION
  if( OptimizationEnabled(db, SQLITE_QueryFlattener|SQLITE_CountOfView)
   && countOfViewOptimization(pParse, p)
  ){
    if( db->mallocFailed ) goto select_end;
    pEList = p->pEList;
    pTabList = p->pSrc;
  }
#endif


  for(i=0; i<pTabList->nSrc; i++){
    struct SrcList_item *pItem = &pTabList->a[i];
    SelectDest dest;
    Select *pSub;
#if !defined(SQLITE_OMIT_SUBQUERY) || !defined(SQLITE_OMIT_VIEW)
    const char *zSavedAuthContext;
#endif


    if( pItem->colUsed==0 && pItem->zName!=0 ){
      sqlite3AuthCheck(pParse, SQLITE_READ, pItem->zName, "", pItem->zDatabase);
    }

#if !defined(SQLITE_OMIT_SUBQUERY) || !defined(SQLITE_OMIT_VIEW)


    pSub = pItem->pSelect;
    if( pSub==0 ) continue;


    testcase( pItem->addrFillSub!=0 );


    pParse->nHeight += sqlite3SelectExprHeight(p);


    if( OptimizationEnabled(db, SQLITE_PushDown)
     && pushDownWhereTerms(pParse, pSub, p->pWhere, pItem->iCursor,
                           (pItem->fg.jointype & JT_OUTER)!=0)
    ){
#if SELECTTRACE_ENABLED
      if( sqlite3SelectTrace & 0x100 ){
        SELECTTRACE(0x100,pParse,p,
            ("After WHERE-clause push-down into subquery %d:\n", pSub->selId));
        sqlite3TreeViewSelect(0, p, 0);
      }
#endif
    }else{
      SELECTTRACE(0x100,pParse,p,("Push-down not possible\n"));
    }

    zSavedAuthContext = pParse->zAuthContext;
    pParse->zAuthContext = pItem->zName;


    if( i==0
     && (pTabList->nSrc==1
            || (pTabList->a[1].fg.jointype&(JT_LEFT|JT_CROSS))!=0)
    ){


      int addrTop = sqlite3VdbeCurrentAddr(v)+1;

      pItem->regReturn = ++pParse->nMem;
      sqlite3VdbeAddOp3(v, OP_InitCoroutine, pItem->regReturn, 0, addrTop);
      VdbeComment((v, "%s", pItem->pTab->zName));
      pItem->addrFillSub = addrTop;
      sqlite3SelectDestInit(&dest, SRT_Coroutine, pItem->regReturn);
      ExplainQueryPlan((pParse, 1, "CO-ROUTINE %u", pSub->selId));
      sqlite3Select(pParse, pSub, &dest);
      pItem->pTab->nRowLogEst = pSub->nSelectRow;
      pItem->fg.viaCoroutine = 1;
      pItem->regResult = dest.iSdst;
      sqlite3VdbeEndCoroutine(v, pItem->regReturn);
      sqlite3VdbeJumpHere(v, addrTop-1);
      sqlite3ClearTempRegCache(pParse);
    }else{


      int topAddr;
      int onceAddr = 0;
      int retAddr;
      struct SrcList_item *pPrior;

      testcase( pItem->addrFillSub==0 );
      pItem->regReturn = ++pParse->nMem;
      topAddr = sqlite3VdbeAddOp2(v, OP_Integer, 0, pItem->regReturn);
      pItem->addrFillSub = topAddr+1;
      if( pItem->fg.isCorrelated==0 ){


        onceAddr = sqlite3VdbeAddOp0(v, OP_Once); VdbeCoverage(v);
        VdbeComment((v, "materialize \"%s\"", pItem->pTab->zName));
      }else{
        VdbeNoopComment((v, "materialize \"%s\"", pItem->pTab->zName));
      }
      pPrior = isSelfJoinView(pTabList, pItem);
      if( pPrior ){
        sqlite3VdbeAddOp2(v, OP_OpenDup, pItem->iCursor, pPrior->iCursor);
        assert( pPrior->pSelect!=0 );
        pSub->nSelectRow = pPrior->pSelect->nSelectRow;
      }else{
        sqlite3SelectDestInit(&dest, SRT_EphemTab, pItem->iCursor);
        ExplainQueryPlan((pParse, 1, "MATERIALIZE %u", pSub->selId));
        sqlite3Select(pParse, pSub, &dest);
      }
      pItem->pTab->nRowLogEst = pSub->nSelectRow;
      if( onceAddr ) sqlite3VdbeJumpHere(v, onceAddr);
      retAddr = sqlite3VdbeAddOp1(v, OP_Return, pItem->regReturn);
      VdbeComment((v, "end %s", pItem->pTab->zName));
      sqlite3VdbeChangeP1(v, topAddr, retAddr);
      sqlite3ClearTempRegCache(pParse);
    }
    if( db->mallocFailed ) goto select_end;
    pParse->nHeight -= sqlite3SelectExprHeight(p);
    pParse->zAuthContext = zSavedAuthContext;
#endif
  }


  pEList = p->pEList;
  pWhere = p->pWhere;
  pGroupBy = p->pGroupBy;
  pHaving = p->pHaving;
  sDistinct.isTnct = (p->selFlags & SF_Distinct)!=0;

#if SELECTTRACE_ENABLED
  if( sqlite3SelectTrace & 0x400 ){
    SELECTTRACE(0x400,pParse,p,("After all FROM-clause analysis:\n"));
    sqlite3TreeViewSelect(0, p, 0);
  }
#endif


  if( (p->selFlags & (SF_Distinct|SF_Aggregate))==SF_Distinct
   && sqlite3ExprListCompare(sSort.pOrderBy, pEList, -1)==0
   && p->pWin==0
  ){
    p->selFlags &= ~SF_Distinct;
    pGroupBy = p->pGroupBy = sqlite3ExprListDup(db, pEList, 0);


    assert( sDistinct.isTnct );

#if SELECTTRACE_ENABLED
    if( sqlite3SelectTrace & 0x400 ){
      SELECTTRACE(0x400,pParse,p,("Transform DISTINCT into GROUP BY:\n"));
      sqlite3TreeViewSelect(0, p, 0);
    }
#endif
  }


  if( sSort.pOrderBy ){
    KeyInfo *pKeyInfo;
    pKeyInfo = sqlite3KeyInfoFromExprList(
        pParse, sSort.pOrderBy, 0, pEList->nExpr);
    sSort.iECursor = pParse->nTab++;
    sSort.addrSortIndex =
      sqlite3VdbeAddOp4(v, OP_OpenEphemeral,
          sSort.iECursor, sSort.pOrderBy->nExpr+1+pEList->nExpr, 0,
          (char*)pKeyInfo, P4_KEYINFO
      );
  }else{
    sSort.addrSortIndex = -1;
  }


  if( pDest->eDest==SRT_EphemTab ){
    sqlite3VdbeAddOp2(v, OP_OpenEphemeral, pDest->iSDParm, pEList->nExpr);
  }


  iEnd = sqlite3VdbeMakeLabel(pParse);
  if( (p->selFlags & SF_FixedLimit)==0 ){
    p->nSelectRow = 320;
  }
  computeLimitRegisters(pParse, p, iEnd);
  if( p->iLimit==0 && sSort.addrSortIndex>=0 ){
    sqlite3VdbeChangeOpcode(v, sSort.addrSortIndex, OP_SorterOpen);
    sSort.sortFlags |= SORTFLAG_UseSorter;
  }


  if( p->selFlags & SF_Distinct ){
    sDistinct.tabTnct = pParse->nTab++;
    sDistinct.addrTnct = sqlite3VdbeAddOp4(v, OP_OpenEphemeral,
                       sDistinct.tabTnct, 0, 0,
                       (char*)sqlite3KeyInfoFromExprList(pParse, p->pEList,0,0),
                       P4_KEYINFO);
    sqlite3VdbeChangeP5(v, BTREE_UNORDERED);
    sDistinct.eTnctType = WHERE_DISTINCT_UNORDERED;
  }else{
    sDistinct.eTnctType = WHERE_DISTINCT_NOOP;
  }

  if( !isAgg && pGroupBy==0 ){

    u16 wctrlFlags = (sDistinct.isTnct ? WHERE_WANT_DISTINCT : 0)
                   | (p->selFlags & SF_FixedLimit);
#ifndef SQLITE_OMIT_WINDOWFUNC
    Window *pWin = p->pWin;
    if( pWin ){
      sqlite3WindowCodeInit(pParse, pWin);
    }
#endif
    assert( WHERE_USE_LIMIT==SF_FixedLimit );


    SELECTTRACE(1,pParse,p,("WhereBegin\n"));
    pWInfo = sqlite3WhereBegin(pParse, pTabList, pWhere, sSort.pOrderBy,
                               p->pEList, wctrlFlags, p->nSelectRow);
    if( pWInfo==0 ) goto select_end;
    if( sqlite3WhereOutputRowCount(pWInfo) < p->nSelectRow ){
      p->nSelectRow = sqlite3WhereOutputRowCount(pWInfo);
    }
    if( sDistinct.isTnct && sqlite3WhereIsDistinct(pWInfo) ){
      sDistinct.eTnctType = sqlite3WhereIsDistinct(pWInfo);
    }
    if( sSort.pOrderBy ){
      sSort.nOBSat = sqlite3WhereIsOrdered(pWInfo);
      sSort.labelOBLopt = sqlite3WhereOrderByLimitOptLabel(pWInfo);
      if( sSort.nOBSat==sSort.pOrderBy->nExpr ){
        sSort.pOrderBy = 0;
      }
    }


    if( sSort.addrSortIndex>=0 && sSort.pOrderBy==0 ){
      sqlite3VdbeChangeToNoop(v, sSort.addrSortIndex);
    }

    assert( p->pEList==pEList );
#ifndef SQLITE_OMIT_WINDOWFUNC
    if( pWin ){
      int addrGosub = sqlite3VdbeMakeLabel(pParse);
      int iCont = sqlite3VdbeMakeLabel(pParse);
      int iBreak = sqlite3VdbeMakeLabel(pParse);
      int regGosub = ++pParse->nMem;

      sqlite3WindowCodeStep(pParse, p, pWInfo, regGosub, addrGosub);

      sqlite3VdbeAddOp2(v, OP_Goto, 0, iBreak);
      sqlite3VdbeResolveLabel(v, addrGosub);
      VdbeNoopComment((v, "inner-loop subroutine"));
      sSort.labelOBLopt = 0;
      selectInnerLoop(pParse, p, -1, &sSort, &sDistinct, pDest, iCont, iBreak);
      sqlite3VdbeResolveLabel(v, iCont);
      sqlite3VdbeAddOp1(v, OP_Return, regGosub);
      VdbeComment((v, "end inner-loop subroutine"));
      sqlite3VdbeResolveLabel(v, iBreak);
    }else
#endif
    {

      selectInnerLoop(pParse, p, -1, &sSort, &sDistinct, pDest,
          sqlite3WhereContinueLabel(pWInfo),
          sqlite3WhereBreakLabel(pWInfo));


      sqlite3WhereEnd(pWInfo);
    }
  }else{


    NameContext sNC;
    int iAMem;
    int iBMem;
    int iUseFlag;


    int iAbortFlag;
    int groupBySort;
    int addrEnd;
    int sortPTab = 0;
    int sortOut = 0;
    int orderByGrp = 0;


    if( pGroupBy ){
      int k;
      struct ExprList_item *pItem;

      for(k=p->pEList->nExpr, pItem=p->pEList->a; k>0; k--, pItem++){
        pItem->u.x.iAlias = 0;
      }
      for(k=pGroupBy->nExpr, pItem=pGroupBy->a; k>0; k--, pItem++){
        pItem->u.x.iAlias = 0;
      }
      assert( 66==sqlite3LogEst(100) );
      if( p->nSelectRow>66 ) p->nSelectRow = 66;


      if( sSort.pOrderBy && pGroupBy->nExpr==sSort.pOrderBy->nExpr ){
        int ii;


        for(ii=0; ii<pGroupBy->nExpr; ii++){
          u8 sortFlags = sSort.pOrderBy->a[ii].sortFlags & KEYINFO_ORDER_DESC;
          pGroupBy->a[ii].sortFlags = sortFlags;
        }
        if( sqlite3ExprListCompare(pGroupBy, sSort.pOrderBy, -1)==0 ){
          orderByGrp = 1;
        }
      }
    }else{
      assert( 0==sqlite3LogEst(1) );
      p->nSelectRow = 0;
    }


    addrEnd = sqlite3VdbeMakeLabel(pParse);


    memset(&sNC, 0, sizeof(sNC));
    sNC.pParse = pParse;
    sNC.pSrcList = pTabList;
    sNC.uNC.pAggInfo = &sAggInfo;
    VVA_ONLY( sNC.ncFlags = NC_UAggInfo; )
    sAggInfo.mnReg = pParse->nMem+1;
    sAggInfo.nSortingColumn = pGroupBy ? pGroupBy->nExpr : 0;
    sAggInfo.pGroupBy = pGroupBy;
    sqlite3ExprAnalyzeAggList(&sNC, pEList);
    sqlite3ExprAnalyzeAggList(&sNC, sSort.pOrderBy);
    if( pHaving ){
      if( pGroupBy ){
        assert( pWhere==p->pWhere );
        assert( pHaving==p->pHaving );
        assert( pGroupBy==p->pGroupBy );
        havingToWhere(pParse, p);
        pWhere = p->pWhere;
      }
      sqlite3ExprAnalyzeAggregates(&sNC, pHaving);
    }
    sAggInfo.nAccumulator = sAggInfo.nColumn;
    if( p->pGroupBy==0 && p->pHaving==0 && sAggInfo.nFunc==1 ){
      minMaxFlag = minMaxQuery(db, sAggInfo.aFunc[0].pExpr, &pMinMaxOrderBy);
    }else{
      minMaxFlag = WHERE_ORDERBY_NORMAL;
    }
    for(i=0; i<sAggInfo.nFunc; i++){
      Expr *pExpr = sAggInfo.aFunc[i].pExpr;
      assert( !ExprHasProperty(pExpr, EP_xIsSelect) );
      sNC.ncFlags |= NC_InAggFunc;
      sqlite3ExprAnalyzeAggList(&sNC, pExpr->x.pList);
#ifndef SQLITE_OMIT_WINDOWFUNC
      assert( !IsWindowFunc(pExpr) );
      if( ExprHasProperty(pExpr, EP_WinFunc) ){
        sqlite3ExprAnalyzeAggregates(&sNC, pExpr->y.pWin->pFilter);
      }
#endif
      sNC.ncFlags &= ~NC_InAggFunc;
    }
    sAggInfo.mxReg = pParse->nMem;
    if( db->mallocFailed ) goto select_end;
#if SELECTTRACE_ENABLED
    if( sqlite3SelectTrace & 0x400 ){
      int ii;
      SELECTTRACE(0x400,pParse,p,("After aggregate analysis:\n"));
      sqlite3TreeViewSelect(0, p, 0);
      for(ii=0; ii<sAggInfo.nColumn; ii++){
        sqlite3DebugPrintf("agg-column[%d] iMem=%d\n",
            ii, sAggInfo.aCol[ii].iMem);
        sqlite3TreeViewExpr(0, sAggInfo.aCol[ii].pExpr, 0);
      }
      for(ii=0; ii<sAggInfo.nFunc; ii++){
        sqlite3DebugPrintf("agg-func[%d]: iMem=%d\n",
            ii, sAggInfo.aFunc[ii].iMem);
        sqlite3TreeViewExpr(0, sAggInfo.aFunc[ii].pExpr, 0);
      }
    }
#endif


    if( pGroupBy ){
      KeyInfo *pKeyInfo;
      int addr1;
      int addrOutputRow;
      int regOutputRow;
      int addrSetAbort;
      int addrTopOfLoop;
      int addrSortingIdx;
      int addrReset;
      int regReset;


      sAggInfo.sortingIdx = pParse->nTab++;
      pKeyInfo = sqlite3KeyInfoFromExprList(pParse,pGroupBy,0,sAggInfo.nColumn);
      addrSortingIdx = sqlite3VdbeAddOp4(v, OP_SorterOpen,
          sAggInfo.sortingIdx, sAggInfo.nSortingColumn,
          0, (char*)pKeyInfo, P4_KEYINFO);


      iUseFlag = ++pParse->nMem;
      iAbortFlag = ++pParse->nMem;
      regOutputRow = ++pParse->nMem;
      addrOutputRow = sqlite3VdbeMakeLabel(pParse);
      regReset = ++pParse->nMem;
      addrReset = sqlite3VdbeMakeLabel(pParse);
      iAMem = pParse->nMem + 1;
      pParse->nMem += pGroupBy->nExpr;
      iBMem = pParse->nMem + 1;
      pParse->nMem += pGroupBy->nExpr;
      sqlite3VdbeAddOp2(v, OP_Integer, 0, iAbortFlag);
      VdbeComment((v, "clear abort flag"));
      sqlite3VdbeAddOp3(v, OP_Null, 0, iAMem, iAMem+pGroupBy->nExpr-1);


      sqlite3VdbeAddOp2(v, OP_Gosub, regReset, addrReset);
      SELECTTRACE(1,pParse,p,("WhereBegin\n"));
      pWInfo = sqlite3WhereBegin(pParse, pTabList, pWhere, pGroupBy, 0,
          WHERE_GROUPBY | (orderByGrp ? WHERE_SORTBYGROUP : 0), 0
      );
      if( pWInfo==0 ) goto select_end;
      if( sqlite3WhereIsOrdered(pWInfo)==pGroupBy->nExpr ){


        groupBySort = 0;
      }else{


        int regBase;
        int regRecord;
        int nCol;
        int nGroupBy;

        explainTempTable(pParse,
            (sDistinct.isTnct && (p->selFlags&SF_Distinct)==0) ?
                    "DISTINCT" : "GROUP BY");

        groupBySort = 1;
        nGroupBy = pGroupBy->nExpr;
        nCol = nGroupBy;
        j = nGroupBy;
        for(i=0; i<sAggInfo.nColumn; i++){
          if( sAggInfo.aCol[i].iSorterColumn>=j ){
            nCol++;
            j++;
          }
        }
        regBase = sqlite3GetTempRange(pParse, nCol);
        sqlite3ExprCodeExprList(pParse, pGroupBy, regBase, 0, 0);
        j = nGroupBy;
        for(i=0; i<sAggInfo.nColumn; i++){
          struct AggInfo_col *pCol = &sAggInfo.aCol[i];
          if( pCol->iSorterColumn>=j ){
            int r1 = j + regBase;
            sqlite3ExprCodeGetColumnOfTable(v,
                               pCol->pTab, pCol->iTable, pCol->iColumn, r1);
            j++;
          }
        }
        regRecord = sqlite3GetTempReg(pParse);
        sqlite3VdbeAddOp3(v, OP_MakeRecord, regBase, nCol, regRecord);
        sqlite3VdbeAddOp2(v, OP_SorterInsert, sAggInfo.sortingIdx, regRecord);
        sqlite3ReleaseTempReg(pParse, regRecord);
        sqlite3ReleaseTempRange(pParse, regBase, nCol);
        sqlite3WhereEnd(pWInfo);
        sAggInfo.sortingIdxPTab = sortPTab = pParse->nTab++;
        sortOut = sqlite3GetTempReg(pParse);
        sqlite3VdbeAddOp3(v, OP_OpenPseudo, sortPTab, sortOut, nCol);
        sqlite3VdbeAddOp2(v, OP_SorterSort, sAggInfo.sortingIdx, addrEnd);
        VdbeComment((v, "GROUP BY sort")); VdbeCoverage(v);
        sAggInfo.useSortingIdx = 1;
      }


      if( orderByGrp && OptimizationEnabled(db, SQLITE_GroupByOrder)
       && (groupBySort || sqlite3WhereIsSorted(pWInfo))
      ){
        sSort.pOrderBy = 0;
        sqlite3VdbeChangeToNoop(v, sSort.addrSortIndex);
      }


      addrTopOfLoop = sqlite3VdbeCurrentAddr(v);
      if( groupBySort ){
        sqlite3VdbeAddOp3(v, OP_SorterData, sAggInfo.sortingIdx,
                          sortOut, sortPTab);
      }
      for(j=0; j<pGroupBy->nExpr; j++){
        if( groupBySort ){
          sqlite3VdbeAddOp3(v, OP_Column, sortPTab, j, iBMem+j);
        }else{
          sAggInfo.directMode = 1;
          sqlite3ExprCode(pParse, pGroupBy->a[j].pExpr, iBMem+j);
        }
      }
      sqlite3VdbeAddOp4(v, OP_Compare, iAMem, iBMem, pGroupBy->nExpr,
                          (char*)sqlite3KeyInfoRef(pKeyInfo), P4_KEYINFO);
      addr1 = sqlite3VdbeCurrentAddr(v);
      sqlite3VdbeAddOp3(v, OP_Jump, addr1+1, 0, addr1+1); VdbeCoverage(v);


      sqlite3ExprCodeMove(pParse, iBMem, iAMem, pGroupBy->nExpr);
      sqlite3VdbeAddOp2(v, OP_Gosub, regOutputRow, addrOutputRow);
      VdbeComment((v, "output one row"));
      sqlite3VdbeAddOp2(v, OP_IfPos, iAbortFlag, addrEnd); VdbeCoverage(v);
      VdbeComment((v, "check abort flag"));
      sqlite3VdbeAddOp2(v, OP_Gosub, regReset, addrReset);
      VdbeComment((v, "reset accumulator"));


      sqlite3VdbeJumpHere(v, addr1);
      updateAccumulator(pParse, iUseFlag, &sAggInfo);
      sqlite3VdbeAddOp2(v, OP_Integer, 1, iUseFlag);
      VdbeComment((v, "indicate data in accumulator"));


      if( groupBySort ){
        sqlite3VdbeAddOp2(v, OP_SorterNext, sAggInfo.sortingIdx, addrTopOfLoop);
        VdbeCoverage(v);
      }else{
        sqlite3WhereEnd(pWInfo);
        sqlite3VdbeChangeToNoop(v, addrSortingIdx);
      }


      sqlite3VdbeAddOp2(v, OP_Gosub, regOutputRow, addrOutputRow);
      VdbeComment((v, "output final row"));


      sqlite3VdbeGoto(v, addrEnd);


      addrSetAbort = sqlite3VdbeCurrentAddr(v);
      sqlite3VdbeAddOp2(v, OP_Integer, 1, iAbortFlag);
      VdbeComment((v, "set abort flag"));
      sqlite3VdbeAddOp1(v, OP_Return, regOutputRow);
      sqlite3VdbeResolveLabel(v, addrOutputRow);
      addrOutputRow = sqlite3VdbeCurrentAddr(v);
      sqlite3VdbeAddOp2(v, OP_IfPos, iUseFlag, addrOutputRow+2);
      VdbeCoverage(v);
      VdbeComment((v, "Groupby result generator entry point"));
      sqlite3VdbeAddOp1(v, OP_Return, regOutputRow);
      finalizeAggFunctions(pParse, &sAggInfo);
      sqlite3ExprIfFalse(pParse, pHaving, addrOutputRow+1, SQLITE_JUMPIFNULL);
      selectInnerLoop(pParse, p, -1, &sSort,
                      &sDistinct, pDest,
                      addrOutputRow+1, addrSetAbort);
      sqlite3VdbeAddOp1(v, OP_Return, regOutputRow);
      VdbeComment((v, "end groupby result generator"));


      sqlite3VdbeResolveLabel(v, addrReset);
      resetAccumulator(pParse, &sAggInfo);
      sqlite3VdbeAddOp2(v, OP_Integer, 0, iUseFlag);
      VdbeComment((v, "indicate accumulator empty"));
      sqlite3VdbeAddOp1(v, OP_Return, regReset);

    }
    else {
#ifndef SQLITE_OMIT_BTREECOUNT
      Table *pTab;
      if( (pTab = isSimpleCount(p, &sAggInfo))!=0 ){


        const int iDb = sqlite3SchemaToIndex(pParse->db, pTab->pSchema);
        const int iCsr = pParse->nTab++;
        Index *pIdx;
        KeyInfo *pKeyInfo = 0;
        Index *pBest = 0;
        int iRoot = pTab->tnum;

        sqlite3CodeVerifySchema(pParse, iDb);
        sqlite3TableLock(pParse, iDb, pTab->tnum, 0, pTab->zName);


        if( !HasRowid(pTab) ) pBest = sqlite3PrimaryKeyIndex(pTab);
        for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
          if( pIdx->bUnordered==0
           && pIdx->szIdxRow<pTab->szTabRow
           && pIdx->pPartIdxWhere==0
           && (!pBest || pIdx->szIdxRow<pBest->szIdxRow)
          ){
            pBest = pIdx;
          }
        }
        if( pBest ){
          iRoot = pBest->tnum;
          pKeyInfo = sqlite3KeyInfoOfIndex(pParse, pBest);
        }


        sqlite3VdbeAddOp4Int(v, OP_OpenRead, iCsr, iRoot, iDb, 1);
        if( pKeyInfo ){
          sqlite3VdbeChangeP4(v, -1, (char *)pKeyInfo, P4_KEYINFO);
        }
        sqlite3VdbeAddOp2(v, OP_Count, iCsr, sAggInfo.aFunc[0].iMem);
        sqlite3VdbeAddOp1(v, OP_Close, iCsr);
        explainSimpleCount(pParse, pTab, pBest);
      }else
#endif
      {
        int regAcc = 0;


        if( sAggInfo.nAccumulator ){
          for(i=0; i<sAggInfo.nFunc; i++){
            if( ExprHasProperty(sAggInfo.aFunc[i].pExpr, EP_WinFunc) ) continue;
            if( sAggInfo.aFunc[i].pFunc->funcFlags&SQLITE_FUNC_NEEDCOLL ) break;
          }
          if( i==sAggInfo.nFunc ){
            regAcc = ++pParse->nMem;
            sqlite3VdbeAddOp2(v, OP_Integer, 0, regAcc);
          }
        }


        assert( p->pGroupBy==0 );
        resetAccumulator(pParse, &sAggInfo);


        assert( minMaxFlag==WHERE_ORDERBY_NORMAL || pMinMaxOrderBy!=0 );
        assert( pMinMaxOrderBy==0 || pMinMaxOrderBy->nExpr==1 );

        SELECTTRACE(1,pParse,p,("WhereBegin\n"));
        pWInfo = sqlite3WhereBegin(pParse, pTabList, pWhere, pMinMaxOrderBy,
                                   0, minMaxFlag, 0);
        if( pWInfo==0 ){
          goto select_end;
        }
        updateAccumulator(pParse, regAcc, &sAggInfo);
        if( regAcc ) sqlite3VdbeAddOp2(v, OP_Integer, 1, regAcc);
        if( sqlite3WhereIsOrdered(pWInfo)>0 ){
          sqlite3VdbeGoto(v, sqlite3WhereBreakLabel(pWInfo));
          VdbeComment((v, "%s() by index",
                (minMaxFlag==WHERE_ORDERBY_MIN?"min":"max")));
        }
        sqlite3WhereEnd(pWInfo);
        finalizeAggFunctions(pParse, &sAggInfo);
      }

      sSort.pOrderBy = 0;
      sqlite3ExprIfFalse(pParse, pHaving, addrEnd, SQLITE_JUMPIFNULL);
      selectInnerLoop(pParse, p, -1, 0, 0,
                      pDest, addrEnd, addrEnd);
    }
    sqlite3VdbeResolveLabel(v, addrEnd);

  }

  if( sDistinct.eTnctType==WHERE_DISTINCT_UNORDERED ){
    explainTempTable(pParse, "DISTINCT");
  }


  if( sSort.pOrderBy ){
    explainTempTable(pParse,
                     sSort.nOBSat>0 ? "RIGHT PART OF ORDER BY":"ORDER BY");
    assert( p->pEList==pEList );
    generateSortTail(pParse, p, &sSort, pEList->nExpr, pDest);
  }


  sqlite3VdbeResolveLabel(v, iEnd);


  rc = (pParse->nErr>0);


select_end:
  sqlite3ExprListDelete(db, pMinMaxOrderBy);
  sqlite3DbFree(db, sAggInfo.aCol);
  sqlite3DbFree(db, sAggInfo.aFunc);
#if SELECTTRACE_ENABLED
  SELECTTRACE(0x1,pParse,p,("end processing\n"));
  if( (sqlite3SelectTrace & 0x2000)!=0 && ExplainQueryPlanParent(pParse)==0 ){
    sqlite3TreeViewSelect(0, p, 0);
  }
#endif
  ExplainQueryPlanPop(pParse);
  return rc;
}
