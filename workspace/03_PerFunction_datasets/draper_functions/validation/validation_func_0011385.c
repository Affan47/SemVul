rt_tile_get_region(gboolean has_alpha,
                               const GdkPixbuf *src, GdkPixbuf *dest,
                               int pb_x, int pb_y, int pb_w, int pb_h,
                               double offset_x, double offset_y, double scale_x, double scale_y,
                               GdkInterpType interp_type,
                               int check_x, int check_y)
{
	if (!has_alpha)
		{
		if (scale_x == 1.0 && scale_y == 1.0)
			{
			gdk_pixbuf_copy_area(src,
					     -offset_x + pb_x, -offset_y + pb_y,
					     pb_w, pb_h,
					     dest,
					     pb_x, pb_y);
			}
		else
			{
			gdk_pixbuf_scale(src, dest,
					 pb_x, pb_y, pb_w, pb_h,
					 offset_x,
					 offset_y,
					 scale_x, scale_y,
					 interp_type);
			}
		}
	else
		{
		gdk_pixbuf_composite_color(src, dest,
					 pb_x, pb_y, pb_w, pb_h,
					 offset_x,
					 offset_y,
					 scale_x, scale_y,
					 interp_type,
					 255, check_x, check_y,
					 PR_ALPHA_CHECK_SIZE, PR_ALPHA_CHECK1, PR_ALPHA_CHECK2);
		}
}
