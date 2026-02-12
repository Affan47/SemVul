static WhereTerm *whereScanInit(
  WhereScan *pScan,
  WhereClause *pWC,
  int iCur,
  int iColumn,
  u32 opMask,
  Index *pIdx
){
  pScan->pOrigWC = pWC;
  pScan->pWC = pWC;
  pScan->pIdxExpr = 0;
  pScan->idxaff = 0;
  pScan->zCollName = 0;
  pScan->opMask = opMask;
  pScan->k = 0;
  pScan->aiCur[0] = iCur;
  pScan->nEquiv = 1;
  pScan->iEquiv = 1;
  if( pIdx ){
    int j = iColumn;
    iColumn = pIdx->aiColumn[j];
    if( iColumn==pIdx->pTable->iPKey ){
      iColumn = XN_ROWID;
    }else if( iColumn>=0 ){
      pScan->idxaff = pIdx->pTable->aCol[iColumn].affinity;
      pScan->zCollName = pIdx->azColl[j];
    }else if( iColumn==XN_EXPR ){
      pScan->pIdxExpr = pIdx->aColExpr->a[j].pExpr;
      pScan->zCollName = pIdx->azColl[j];
      pScan->aiColumn[0] = XN_EXPR;
      return whereScanInitIndexExpr(pScan);
    }
  }else if( iColumn==XN_EXPR ){
    return 0;
  }
  pScan->aiColumn[0] = iColumn;
  return whereScanNext(pScan);
}
