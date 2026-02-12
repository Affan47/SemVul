static int resolveOrderByTermToExprList(
  Parse *pParse,
  Select *pSelect,
  Expr *pE
){
  int i;
  ExprList *pEList;
  NameContext nc;
  sqlite3 *db;
  int rc;
  u8 savedSuppErr;

  assert( sqlite3ExprIsInteger(pE, &i)==0 );
  pEList = pSelect->pEList;


  memset(&nc, 0, sizeof(nc));
  nc.pParse = pParse;
  nc.pSrcList = pSelect->pSrc;
  nc.uNC.pEList = pEList;
  nc.ncFlags = NC_AllowAgg|NC_UEList;
  nc.nErr = 0;
  db = pParse->db;
  savedSuppErr = db->suppressErr;
  db->suppressErr = 1;
  rc = sqlite3ResolveExprNames(&nc, pE);
  db->suppressErr = savedSuppErr;
  if( rc ) return 0;


  for(i=0; i<pEList->nExpr; i++){
    if( sqlite3ExprCompare(0, pEList->a[i].pExpr, pE, -1)<2 ){
      return i+1;
    }
  }


  return 0;
}
