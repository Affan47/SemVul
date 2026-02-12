void sqlite3VdbeScanStatus(
  Vdbe *p,
  int addrExplain,
  int addrLoop,
  int addrVisit,
  LogEst nEst,
  const char *zName
){
  sqlite3_int64 nByte = (p->nScan+1) * sizeof(ScanStatus);
  ScanStatus *aNew;
  aNew = (ScanStatus*)sqlite3DbRealloc(p->db, p->aScan, nByte);
  if( aNew ){
    ScanStatus *pNew = &aNew[p->nScan++];
    pNew->addrExplain = addrExplain;
    pNew->addrLoop = addrLoop;
    pNew->addrVisit = addrVisit;
    pNew->nEst = nEst;
    pNew->zName = sqlite3DbStrDup(p->db, zName);
    p->aScan = aNew;
  }
}
