int sqlite3ExprCodeGetColumn(
  Parse *pParse,
  Table *pTab,
  int iColumn,
  int iTable,
  int iReg,
  u8 p5
){
  assert( pParse->pVdbe!=0 );
  sqlite3ExprCodeGetColumnOfTable(pParse->pVdbe, pTab, iTable, iColumn, iReg);
  if( p5 ){
    VdbeOp *pOp = sqlite3VdbeGetOp(pParse->pVdbe,-1);
    if( pOp->opcode==OP_Column ) pOp->p5 = p5;
  }
  return iReg;
}
