static LogEst whereSortingCost(
  WhereInfo *pWInfo,
  LogEst nRow,
  int nOrderBy,
  int nSorted
){


  LogEst rScale, rSortCost;
  assert( nOrderBy>0 && 66==sqlite3LogEst(100) );
  rScale = sqlite3LogEst((nOrderBy-nSorted)*100/nOrderBy) - 66;
  rSortCost = nRow + rScale + 16;


  if( (pWInfo->wctrlFlags & WHERE_USE_LIMIT)!=0 && pWInfo->iLimit<nRow ){
    nRow = pWInfo->iLimit;
  }else if( (pWInfo->wctrlFlags & WHERE_WANT_DISTINCT) ){


    if( nRow>10 ){ nRow -= 10;  assert( 10==sqlite3LogEst(2) ); }
  }
  rSortCost += estLog(nRow);
  return rSortCost;
}
