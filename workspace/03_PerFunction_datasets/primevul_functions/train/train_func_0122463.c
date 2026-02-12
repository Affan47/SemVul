static void whereLikeOptimizationStringFixup(
  Vdbe *v,
  WhereLevel *pLevel,
  WhereTerm *pTerm
){
  if( pTerm->wtFlags & TERM_LIKEOPT ){
    VdbeOp *pOp;
    assert( pLevel->iLikeRepCntr>0 );
    pOp = sqlite3VdbeGetOp(v, -1);
    assert( pOp!=0 );
    assert( pOp->opcode==OP_String8
            || pTerm->pWC->pWInfo->pParse->db->mallocFailed );
    pOp->p3 = (int)(pLevel->iLikeRepCntr>>1);
    pOp->p5 = (u8)(pLevel->iLikeRepCntr&1);
  }
}
