sqlite3DequoteExpr(Expr *p){
  if( ExprHasAnyProperty(p, EP_Dequoted) ){
    return;
  }
  ExprSetProperty(p, EP_Dequoted);
  if( p->token.dyn==0 ){
    sqlite3TokenCopy(&p->token, &p->token);
  }
  sqlite3Dequote((char*)p->token.z);
}
