sqliteExprDup(Expr *p){
  Expr *pNew;
  if( p==0 ) return 0;
  pNew = sqliteMallocRaw( sizeof(*p) );
  if( pNew==0 ) return 0;
  memcpy(pNew, p, sizeof(*pNew));
  if( p->token.z!=0 ){
    pNew->token.z = sqliteStrNDup(p->token.z, p->token.n);
    pNew->token.dyn = 1;
  }else{
    assert( pNew->token.z==0 );
  }
  pNew->span.z = 0;
  pNew->pLeft = sqliteExprDup(p->pLeft);
  pNew->pRight = sqliteExprDup(p->pRight);
  pNew->pList = sqliteExprListDup(p->pList);
  pNew->pSelect = sqliteSelectDup(p->pSelect);
  return pNew;
}
