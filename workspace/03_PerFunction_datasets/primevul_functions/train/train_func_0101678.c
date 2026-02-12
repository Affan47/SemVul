static void fts3PutDeltaVarint(
  char **pp,
  sqlite3_int64 *piPrev,
  sqlite3_int64 iVal
){
  assert( iVal-*piPrev > 0 || (*piPrev==0 && iVal==0) );
  *pp += sqlite3Fts3PutVarint(*pp, iVal-*piPrev);
  *piPrev = iVal;
}
