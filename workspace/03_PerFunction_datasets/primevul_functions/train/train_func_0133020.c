void do_warn(SV* h, int rc, char* what)
{
  dTHX;
  D_imp_xxh(h);
  STRLEN lna;

  SV *errstr = DBIc_ERRSTR(imp_xxh);
  sv_setiv(DBIc_ERR(imp_xxh), (IV)rc);
  sv_setpv(errstr, what);

  if (DBIc_TRACE_LEVEL(imp_xxh) >= 2)
    PerlIO_printf(DBIc_LOGPIO(imp_xxh), "%s warning %d recorded: %s\n",
    what, rc, SvPV(errstr,lna));
  warn("%s", what);
}
