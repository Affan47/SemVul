static int whereEqualScanEst(
  Parse *pParse,
  WhereLoopBuilder *pBuilder,
  Expr *pExpr,
  tRowcnt *pnRow
){
  Index *p = pBuilder->pNew->u.btree.pIndex;
  int nEq = pBuilder->pNew->u.btree.nEq;
  UnpackedRecord *pRec = pBuilder->pRec;
  int rc;
  tRowcnt a[2];
  int bOk;

  assert( nEq>=1 );
  assert( nEq<=p->nColumn );
  assert( p->aSample!=0 );
  assert( p->nSample>0 );
  assert( pBuilder->nRecValid<nEq );


  if( pBuilder->nRecValid<(nEq-1) ){
    return SQLITE_NOTFOUND;
  }


  if( nEq>=p->nColumn ){
    *pnRow = 1;
    return SQLITE_OK;
  }

  rc = sqlite3Stat4ProbeSetValue(pParse, p, &pRec, pExpr, 1, nEq-1, &bOk);
  pBuilder->pRec = pRec;
  if( rc!=SQLITE_OK ) return rc;
  if( bOk==0 ) return SQLITE_NOTFOUND;
  pBuilder->nRecValid = nEq;

  whereKeyStats(pParse, p, pRec, 0, a);
  WHERETRACE(0x10,("equality scan regions %s(%d): %d\n",
                   p->zName, nEq-1, (int)a[1]));
  *pnRow = a[1];

  return rc;
}
