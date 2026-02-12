static void fts3GetDeltaVarint3(
  char **pp,
  char *pEnd,
  int bDescIdx,
  sqlite3_int64 *pVal
){
  if( *pp>=pEnd ){
    *pp = 0;
  }else{
    sqlite3_int64 iVal;
    *pp += sqlite3Fts3GetVarint(*pp, &iVal);
    if( bDescIdx ){
      *pVal -= iVal;
    }else{
      *pVal += iVal;
    }
  }
}
