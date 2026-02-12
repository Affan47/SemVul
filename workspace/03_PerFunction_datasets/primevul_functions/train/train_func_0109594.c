static int whereUsablePartialIndex(
  int iTab,
  u8 jointype,
  WhereClause *pWC,
  Expr *pWhere
){
  int i;
  WhereTerm *pTerm;
  Parse *pParse;

  if( jointype & JT_LTORJ ) return 0;
  pParse = pWC->pWInfo->pParse;
  while( pWhere->op==TK_AND ){
    if( !whereUsablePartialIndex(iTab,jointype,pWC,pWhere->pLeft) ) return 0;
    pWhere = pWhere->pRight;
  }
  if( pParse->db->flags & SQLITE_EnableQPSG ) pParse = 0;
  for(i=0, pTerm=pWC->a; i<pWC->nTerm; i++, pTerm++){
    Expr *pExpr;
    pExpr = pTerm->pExpr;
    if( (!ExprHasProperty(pExpr, EP_OuterON) || pExpr->w.iJoin==iTab)
     && ((jointype & JT_OUTER)==0 || ExprHasProperty(pExpr, EP_OuterON))
     && sqlite3ExprImpliesExpr(pParse, pExpr, pWhere, iTab)
     && (pTerm->wtFlags & TERM_VNULL)==0
    ){
      return 1;
    }
  }
  return 0;
}
