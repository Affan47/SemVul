int sqlite3ResolveExprListNames(
  NameContext *pNC,
  ExprList *pList
){
  int i;
  if( pList ){
    for(i=0; i<pList->nExpr; i++){
      if( sqlite3ResolveExprNames(pNC, pList->a[i].pExpr) ) return WRC_Abort;
    }
  }
  return WRC_Continue;
}
