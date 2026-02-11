gt_color_name(const int garmin_index)
{
  if ((garmin_index >= 0) && (garmin_index < GT_COLORS_CT)) {
    return gt_colors[garmin_index].name;
  } else {
    return gt_colors[0].name;
  }
}
