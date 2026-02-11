XS_gotow(pTHX_ CV *perlcv)
{
  int    num;
  GList *worldpos;
  dXSARGS;

  if (items < 1) {
    warn(_("%s: Too few arguments"), "gotow");
    XSRETURN_EMPTY;
  } else {
    if (SvIOK(ST(0))) {
      num = SvIV(ST(0));
    } else {
      worldpos = g_list_find_custom(open_worlds,
                                    SvPV_nolen(ST(0)),
                                    (GCompareFunc) world_name_comparer);
      num = g_list_position(open_worlds, worldpos);
    }
  }

  if (num < 0 || num >= g_list_length(open_worlds)) {
    warn(_("%s: No such world"), "gotow");
    XSRETURN_EMPTY;
  }

  set_focused_world(num);

  XSRETURN_EMPTY;
}
