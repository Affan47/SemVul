int sqlite3VdbeAddOp4Dup8(
  Vdbe *p,
  int op,
  int p1,
  int p2,
  int p3,
  const u8 *zP4,
  int p4type
){
  char *p4copy = sqlite3DbMallocRawNN(sqlite3VdbeDb(p), 8);
  if( p4copy ) memcpy(p4copy, zP4, 8);
  return sqlite3VdbeAddOp4(p, op, p1, p2, p3, p4copy, p4type);
}
