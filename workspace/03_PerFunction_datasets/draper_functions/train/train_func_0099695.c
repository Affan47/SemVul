geoniche_geostuff(const waypoint* wpt)
{
  char* gs = NULL, *tmp1, *tmp2, *tmp3;
  char tbuf[10240];

  if (!wpt->gc_data->terr) {
    return NULL;
  }

  snprintf(tbuf, sizeof(tbuf), "\n%s by %s\n\n", gs_get_cachetype(wpt->gc_data->type), wpt->gc_data->placer);
  gs = xstrappend(gs, tbuf);


  snprintf(tbuf, sizeof(tbuf), "Container: %s\nDifficulty: %3.1f\nTerrain: %3.1f\n\n", gs_get_container(wpt->gc_data->container), wpt->gc_data->diff/10.0, wpt->gc_data->terr/10.0);
  gs = xstrappend(gs, tbuf);

  tmp1 = strip_html(&wpt->gc_data->desc_short);
  tmp2 = strip_html(&wpt->gc_data->desc_long);
  gs = xstrappend(gs, tmp1);
  gs = xstrappend(gs, tmp2);

  tmp3 = rot13(wpt->gc_data->hint);
  snprintf(tbuf, sizeof(tbuf), "\n\nHint: %s\n", tmp3);
  gs = xstrappend(gs, tbuf);

  xfree(tmp1);
  xfree(tmp2);
  xfree(tmp3);

  tmp1 = enscape(gs);
  xfree(gs);

  return tmp1;
}
