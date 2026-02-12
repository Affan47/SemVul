Expr *sqlite3Expr(
  sqlite3 *db,
  int op,
  const char *zToken
){
  Token x;
  x.z = zToken;
  x.n = sqlite3Strlen30(zToken);
  return sqlite3ExprAlloc(db, op, &x, 0);
}
