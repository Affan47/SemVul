static int whereInScanEst(
  Parse *pParse,
  WhereLoopBuilder *pBuilder,
  ExprList *pList,
  tRowcnt *pnRow
){
  Index *p = pBuilder->pNew->u.btree.pIndex;
  i64 nRow0 = sqlite3LogEstToInt(p->aiRowLogEst[0]);
  int nRecValid = pBuilder->nRecValid;
  int rc = SQLITE_OK;
  tRowcnt nEst;
  tRowcnt nRowEst = 0;
  int i;

  assert( p->aSample!=0 );
  for(i=0; rc==SQLITE_OK && i<pList->nExpr; i++){
    nEst = nRow0;
    rc = whereEqualScanEst(pParse, pBuilder, pList->a[i].pExpr, &nEst);
    nRowEst += nEst;
    pBuilder->nRecValid = nRecValid;
  }

  if( rc==SQLITE_OK ){
    if( nRowEst > nRow0 ) nRowEst = nRow0;
    *pnRow = nRowEst;
    WHERETRACE(0x10,("IN row estimate: est=%d\n", nRowEst));
  }
  assert( pBuilder->nRecValid==nRecValid );
  return rc;
}
