Expr *sqlite3ExprForVectorField(
  Parse *pParse,
  Expr *pVector,
  int iField
){
  Expr *pRet;
  if( pVector->op==TK_SELECT ){
    assert( pVector->flags & EP_xIsSelect );


    pRet = sqlite3PExpr(pParse, TK_SELECT_COLUMN, 0, 0);
    if( pRet ){
      pRet->iColumn = iField;
      pRet->pLeft = pVector;
    }
    assert( pRet==0 || pRet->iTable==0 );
  }else{
    if( pVector->op==TK_VECTOR ) pVector = pVector->x.pList->a[iField].pExpr;
    pRet = sqlite3ExprDup(pParse->db, pVector, 0);
    sqlite3RenameTokenRemap(pParse, pRet, pVector);
  }
  return pRet;
}
