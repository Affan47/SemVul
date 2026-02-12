static void returnSingleText(
  Vdbe *v,
  const char *zValue
){
  if( zValue ){
    sqlite3VdbeLoadString(v, 1, (const char*)zValue);
    sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 1);
  }
}
