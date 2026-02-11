check_width(unsigned int width, GtStyle *style, GtError *err)
{
  int had_err = 0;
  double margins = MARGINS_DEFAULT;
  if (gt_style_get_num(style,
                       "format", "margins",
                       &margins, NULL, err) == GT_STYLE_QUERY_ERROR) {
    had_err = -1;
  }
  if (!had_err && gt_double_smaller_double(width - 2*margins, 0))
  {
    gt_error_set(err, "layout width must at least be twice the x-margin size "
                      "(2*%.1f=%.1f) but was %u",
                      margins,
                      2*margins,
                      width);
    had_err = -1;
  }
  return had_err;
}
