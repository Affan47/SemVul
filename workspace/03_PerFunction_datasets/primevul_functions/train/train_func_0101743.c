static void fts3ReadNextPos(
  char **pp,
  sqlite3_int64 *pi
){
  if( (**pp)&0xFE ){
    fts3GetDeltaVarint(pp, pi);
    *pi -= 2;
  }else{
    *pi = POSITION_LIST_END;
  }
}
