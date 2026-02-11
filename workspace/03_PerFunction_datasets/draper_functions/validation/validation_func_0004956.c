re_sql_func(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  ReCompiled *pRe;
  const char *zPattern;
  const unsigned char *zStr;
  const char *zErr;

  pRe = sqlite3_get_auxdata(context, 0);
  if( pRe==0 ){
    zPattern = (const char*)sqlite3_value_text(argv[0]);
    if( zPattern==0 ) return;
    zErr = re_compile(&pRe, zPattern, 0);
    if( zErr ){
      sqlite3_result_error(context, zErr, -1);
      return;
    }
    if( pRe==0 ){
      sqlite3_result_error_nomem(context);
      return;
    }
    sqlite3_set_auxdata(context, 0, pRe, (void(*)(void*))re_free);
  }
  zStr = (const unsigned char*)sqlite3_value_text(argv[1]);
  if( zStr!=0 ){
    sqlite3_result_int(context, re_match(pRe, zStr, -1));
  }
}
