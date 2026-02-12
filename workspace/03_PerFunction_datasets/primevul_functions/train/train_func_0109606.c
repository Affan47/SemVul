static SQLITE_NOINLINE void sqlite3ConstructBloomFilter(
  WhereInfo *pWInfo,
  int iLevel,
  WhereLevel *pLevel,
  Bitmask notReady
){
  int addrOnce;
  int addrTop;
  int addrCont;
  const WhereTerm *pTerm;
  const WhereTerm *pWCEnd;
  Parse *pParse = pWInfo->pParse;
  Vdbe *v = pParse->pVdbe;
  WhereLoop *pLoop = pLevel->pWLoop;
  int iCur;

  assert( pLoop!=0 );
  assert( v!=0 );
  assert( pLoop->wsFlags & WHERE_BLOOMFILTER );

  addrOnce = sqlite3VdbeAddOp0(v, OP_Once); VdbeCoverage(v);
  do{
    const SrcItem *pItem;
    const Table *pTab;
    u64 sz;
    sqlite3WhereExplainBloomFilter(pParse, pWInfo, pLevel);
    addrCont = sqlite3VdbeMakeLabel(pParse);
    iCur = pLevel->iTabCur;
    pLevel->regFilter = ++pParse->nMem;


    pItem = &pWInfo->pTabList->a[pLevel->iFrom];
    assert( pItem!=0 );
    pTab = pItem->pTab;
    assert( pTab!=0 );
    sz = sqlite3LogEstToInt(pTab->nRowLogEst);
    if( sz<10000 ){
      sz = 10000;
    }else if( sz>10000000 ){
      sz = 10000000;
    }
    sqlite3VdbeAddOp2(v, OP_Blob, (int)sz, pLevel->regFilter);

    addrTop = sqlite3VdbeAddOp1(v, OP_Rewind, iCur); VdbeCoverage(v);
    pWCEnd = &pWInfo->sWC.a[pWInfo->sWC.nTerm];
    for(pTerm=pWInfo->sWC.a; pTerm<pWCEnd; pTerm++){
      Expr *pExpr = pTerm->pExpr;
      if( (pTerm->wtFlags & TERM_VIRTUAL)==0
       && sqlite3ExprIsTableConstraint(pExpr, pItem)
      ){
        sqlite3ExprIfFalse(pParse, pTerm->pExpr, addrCont, SQLITE_JUMPIFNULL);
      }
    }
    if( pLoop->wsFlags & WHERE_IPK ){
      int r1 = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp2(v, OP_Rowid, iCur, r1);
      sqlite3VdbeAddOp4Int(v, OP_FilterAdd, pLevel->regFilter, 0, r1, 1);
      sqlite3ReleaseTempReg(pParse, r1);
    }else{
      Index *pIdx = pLoop->u.btree.pIndex;
      int n = pLoop->u.btree.nEq;
      int r1 = sqlite3GetTempRange(pParse, n);
      int jj;
      for(jj=0; jj<n; jj++){
        int iCol = pIdx->aiColumn[jj];
        assert( pIdx->pTable==pItem->pTab );
        sqlite3ExprCodeGetColumnOfTable(v, pIdx->pTable, iCur, iCol,r1+jj);
      }
      sqlite3VdbeAddOp4Int(v, OP_FilterAdd, pLevel->regFilter, 0, r1, n);
      sqlite3ReleaseTempRange(pParse, r1, n);
    }
    sqlite3VdbeResolveLabel(v, addrCont);
    sqlite3VdbeAddOp2(v, OP_Next, pLevel->iTabCur, addrTop+1);
    VdbeCoverage(v);
    sqlite3VdbeJumpHere(v, addrTop);
    pLoop->wsFlags &= ~WHERE_BLOOMFILTER;
    if( OptimizationDisabled(pParse->db, SQLITE_BloomPulldown) ) break;
    while( ++iLevel < pWInfo->nLevel ){
      const SrcItem *pTabItem;
      pLevel = &pWInfo->a[iLevel];
      pTabItem = &pWInfo->pTabList->a[pLevel->iFrom];
      if( pTabItem->fg.jointype & (JT_LEFT|JT_LTORJ) ) continue;
      pLoop = pLevel->pWLoop;
      if( NEVER(pLoop==0) ) continue;
      if( pLoop->prereq & notReady ) continue;
      if( (pLoop->wsFlags & (WHERE_BLOOMFILTER|WHERE_COLUMN_IN))
                 ==WHERE_BLOOMFILTER
      ){


        break;
      }
    }
  }while( iLevel < pWInfo->nLevel );
  sqlite3VdbeJumpHere(v, addrOnce);
}
