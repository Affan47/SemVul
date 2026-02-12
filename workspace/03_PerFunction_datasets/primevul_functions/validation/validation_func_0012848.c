int sqlite3VdbeAddFunctionCall(
  Parse *pParse,
  int p1,
  int p2,
  int p3,
  int nArg,
  const FuncDef *pFunc,
  int eCallCtx
){
  Vdbe *v = pParse->pVdbe;
  int nByte;
  int addr;
  sqlite3_context *pCtx;
  assert( v );
  nByte = sizeof(*pCtx) + (nArg-1)*sizeof(sqlite3_value*);
  pCtx = sqlite3DbMallocRawNN(pParse->db, nByte);
  if( pCtx==0 ){
    assert( pParse->db->mallocFailed );
    freeEphemeralFunction(pParse->db, (FuncDef*)pFunc);
    return 0;
  }
  pCtx->pOut = 0;
  pCtx->pFunc = (FuncDef*)pFunc;
  pCtx->pVdbe = 0;
  pCtx->isError = 0;
  pCtx->argc = nArg;
  pCtx->iOp = sqlite3VdbeCurrentAddr(v);
  addr = sqlite3VdbeAddOp4(v, eCallCtx ? OP_PureFunc : OP_Function,
                           p1, p2, p3, (char*)pCtx, P4_FUNCCTX);
  sqlite3VdbeChangeP5(v, eCallCtx & NC_SelfRef);
  return addr;
}
