void sqlite3VdbeEndCoroutine(Vdbe *v, int regYield){
  sqlite3VdbeAddOp1(v, OP_EndCoroutine, regYield);


  v->pParse->nTempReg = 0;
  v->pParse->nRangeReg = 0;
}
