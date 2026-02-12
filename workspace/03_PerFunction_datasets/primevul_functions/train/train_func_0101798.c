static int fts3EvalNearTrim(
  int nNear,
  char *aTmp,
  char **paPoslist,
  int *pnToken,
  Fts3Phrase *pPhrase
){
  int nParam1 = nNear + pPhrase->nToken;
  int nParam2 = nNear + *pnToken;
  int nNew;
  char *p2;
  char *pOut;
  int res;

  assert( pPhrase->doclist.pList );

  p2 = pOut = pPhrase->doclist.pList;
  res = fts3PoslistNearMerge(
    &pOut, aTmp, nParam1, nParam2, paPoslist, &p2
  );
  if( res ){
    nNew = (int)(pOut - pPhrase->doclist.pList) - 1;
    assert( pPhrase->doclist.pList[nNew]=='\0' );
    assert( nNew<=pPhrase->doclist.nList && nNew>0 );
    memset(&pPhrase->doclist.pList[nNew], 0, pPhrase->doclist.nList - nNew);
    pPhrase->doclist.nList = nNew;
    *paPoslist = pPhrase->doclist.pList;
    *pnToken = pPhrase->nToken;
  }

  return res;
}
