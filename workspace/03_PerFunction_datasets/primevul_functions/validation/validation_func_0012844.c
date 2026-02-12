int sqlite3VdbeAddOp4(
  Vdbe *p,
  int op,
  int p1,
  int p2,
  int p3,
  const char *zP4,
  int p4type
){
  int addr = sqlite3VdbeAddOp3(p, op, p1, p2, p3);
  sqlite3VdbeChangeP4(p, addr, zP4, p4type);
  return addr;
}
