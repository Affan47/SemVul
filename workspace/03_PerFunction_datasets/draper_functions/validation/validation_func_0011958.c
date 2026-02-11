gt_splice_site_info_stream_show_canonical(GtNodeStream *ns, bool show_gc)
{
  GtSpliceSiteInfoStream *ssis;
  gt_assert(ns);
  ssis = gt_splice_site_info_stream_cast(ns);
  return gt_splice_site_info_visitor_show_canonical(ssis
                                                    ->splice_site_info_visitor,
                                                    show_gc);
}
