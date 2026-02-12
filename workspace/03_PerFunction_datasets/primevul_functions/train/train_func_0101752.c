static void fts3GetReverseVarint(
  char **pp,
  char *pStart,
  sqlite3_int64 *pVal
){
  sqlite3_int64 iVal;
  char *p;


  for(p = (*pp)-2; p>=pStart && *p&0x80; p--);
  p++;
  *pp = p;

  sqlite3Fts3GetVarint(p, &iVal);
  *pVal = iVal;
}
