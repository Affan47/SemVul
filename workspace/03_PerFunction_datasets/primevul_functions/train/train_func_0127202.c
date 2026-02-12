static void resolveOutOfRangeError(
  Parse *pParse,
  const char *zType,
  int i,
  int mx
){
  sqlite3ErrorMsg(pParse,
    "%r %s BY term out of range - should be "
    "between 1 and %d", i, zType, mx);
}
