XS_echo(pTHX_ CV *perlcv)
{
  int     i;
  char   *word;
  STRLEN  len;
  FETCHWORLDVARS;
  dXSARGS;

  FETCHWORLD;

  for (i = 1; i < items; ++i) {
    word = SvPV(ST(i), len);
    if (world && world->gui->txtView) {
      ansitextview_append_echoed_string(world->gui, word, len);
    } else {
      printf(word);
    }
  }

  XSRETURN_EMPTY;
}
