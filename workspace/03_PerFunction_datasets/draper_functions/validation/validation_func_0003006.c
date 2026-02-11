gfs_event_filter_read (GtsObject ** o, GtsFile * fp)
{
  GfsDomain * domain;

  if (GTS_OBJECT_CLASS (gfs_event_filter_class ())->parent_class->read)
    (* GTS_OBJECT_CLASS (gfs_event_filter_class ())->parent_class->read)
      (o, fp);
  if (fp->type == GTS_ERROR)
    return;

  if (fp->type != GTS_STRING) {
    gts_file_error (fp, "expecting a string (variable)");
    return;
  }
  domain = GFS_DOMAIN (gfs_object_simulation (*o));
  if ((GFS_EVENT_FILTER (*o)->v = gfs_variable_from_name (domain->variables, fp->token->str))
      == NULL) {
    gts_file_error (fp, "unknown variable `%s'", fp->token->str);
    return;
  }
  gts_file_next_token (fp);

  GFS_EVENT_FILTER (*o)->scale = gfs_read_constant (fp, domain);
  if (fp->type == GTS_ERROR)
    return;
  if (GFS_EVENT_FILTER (*o)->scale <= 0.) {
    gts_file_error (fp, "time scale must be strictly positive");
    return;
  }
}
