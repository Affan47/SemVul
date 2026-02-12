static int fts3PutColNumber(char **pp, int iCol){
  int n = 0;
  if( iCol ){
    char *p = *pp;
    n = 1 + sqlite3Fts3PutVarint(&p[1], iCol);
    *p = 0x01;
    *pp = &p[n];
  }
  return n;
}
