int sqlite3VdbeAddOp4Int(
  Vdbe *p,
  int op,
  int p1,
  int p2,
  int p3,
  int p4
){
  int addr = sqlite3VdbeAddOp3(p, op, p1, p2, p3);
  if( p->db->mallocFailed==0 ){
    VdbeOp *pOp = &p->aOp[addr];
    pOp->p4type = P4_INT32;
    pOp->p4.i = p4;
  }
  return addr;
}
