static void noopStepFunc(
  sqlite3_context *p,
  int n,
  sqlite3_value **a
){
  UNUSED_PARAMETER(p);
  UNUSED_PARAMETER(n);
  UNUSED_PARAMETER(a);
  assert(0);
}
