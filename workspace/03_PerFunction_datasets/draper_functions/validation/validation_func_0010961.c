channel_close_error(long status_230X, long index_231X, long id_232X)
{

 {  ps_write_string("Error: ", (stderr));
  ps_write_string((ps_error_string(status_230X)), (stderr));
  { long ignoreXX;
  PS_WRITE_CHAR(10, (stderr), ignoreXX) }
  ps_write_string(" while closing port ", (stderr));
  if ((3 == (3 & id_232X))) {
    if ((16 == (31 & ((((*((long *) ((((char *) (-3 + id_232X))) + -8))))>>2))))) {
      ps_write_string((((char *)(((char *) (-3 + id_232X))))), (stderr));
      goto L24037;}
    else {
      goto L24025;}}
  else {
    goto L24025;}}
 L24037: {
  { long ignoreXX;
  PS_WRITE_CHAR(10, (stderr), ignoreXX) }
  return;}
 L24025: {
  if ((0 == (3 & id_232X))) {
    ps_write_integer((((index_231X)>>2)), (stderr));
    goto L24037;}
  else {
    ps_write_string("<strange id>", (stderr));
    goto L24037;}}
}
