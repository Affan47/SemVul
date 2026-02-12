static int fts3SyncMethod(sqlite3_vtab *pVtab){


  const u32 nMinMerge = 64;

  Fts3Table *p = (Fts3Table*)pVtab;
  int rc = sqlite3Fts3PendingTermsFlush(p);

  if( rc==SQLITE_OK
   && p->nLeafAdd>(nMinMerge/16)
   && p->nAutoincrmerge && p->nAutoincrmerge!=0xff
  ){
    int mxLevel = 0;
    int A;

    rc = sqlite3Fts3MaxLevel(p, &mxLevel);
    assert( rc==SQLITE_OK || mxLevel==0 );
    A = p->nLeafAdd * mxLevel;
    A += (A/2);
    if( A>(int)nMinMerge ) rc = sqlite3Fts3Incrmerge(p, A, p->nAutoincrmerge);
  }
  sqlite3Fts3SegmentsClose(p);
  return rc;
}
