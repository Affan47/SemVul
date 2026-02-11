gst_video_balance_packed_yuv (GstVideoBalance * videobalance, guint8 * data)
{
  gint x, y;
  guint8 *ydata;
  guint8 *udata, *vdata;
  gint ystride, ustride, vstride;
  gint yoff, uoff, voff;
  GstVideoFormat format;
  gint width, height;
  gint width2, height2;
  guint8 *tabley = videobalance->tabley;
  guint8 **tableu = videobalance->tableu;
  guint8 **tablev = videobalance->tablev;

  format = videobalance->format;
  width = videobalance->width;
  height = videobalance->height;

  ydata =
      data + gst_video_format_get_component_offset (format, 0, width, height);
  ystride = gst_video_format_get_row_stride (format, 0, width);
  yoff = gst_video_format_get_pixel_stride (format, 0);

  for (y = 0; y < height; y++) {
    guint8 *yptr;

    yptr = ydata + y * ystride;
    for (x = 0; x < width; x++) {
      *yptr = tabley[*yptr];
      yptr += yoff;
    }
  }

  width2 = gst_video_format_get_component_width (format, 1, width);
  height2 = gst_video_format_get_component_height (format, 1, height);

  udata =
      data + gst_video_format_get_component_offset (format, 1, width, height);
  vdata =
      data + gst_video_format_get_component_offset (format, 2, width, height);
  ustride = gst_video_format_get_row_stride (format, 1, width);
  vstride = gst_video_format_get_row_stride (format, 1, width);
  uoff = gst_video_format_get_pixel_stride (format, 1);
  voff = gst_video_format_get_pixel_stride (format, 2);

  for (y = 0; y < height2; y++) {
    guint8 *uptr, *vptr;
    guint8 u1, v1;

    uptr = udata + y * ustride;
    vptr = vdata + y * vstride;

    for (x = 0; x < width2; x++) {
      u1 = *uptr;
      v1 = *vptr;

      *uptr = tableu[u1][v1];
      *vptr = tablev[u1][v1];

      uptr += uoff;
      vptr += voff;
    }
  }
}
