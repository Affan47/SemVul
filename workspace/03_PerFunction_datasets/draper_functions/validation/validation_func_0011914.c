gst_avi_demux_invert (GstAviStream * stream, GstBuffer * buf)
{
  GstStructure *s;
  gint y, w, h;
  gint bpp, stride;
  guint8 *tmp = NULL;

  if (stream->strh->type != GST_RIFF_FCC_vids)
    return buf;

  if (!gst_avi_demux_is_uncompressed (stream->strh->fcc_handler)) {
    return buf;
  }

  s = gst_caps_get_structure (GST_PAD_CAPS (stream->pad), 0);
  if (!gst_structure_get_int (s, "bpp", &bpp)) {
    GST_WARNING ("Failed to retrieve depth from caps");
    return buf;
  }

  if (stream->strf.vids == NULL) {
    GST_WARNING ("Failed to retrieve vids for stream");
    return buf;
  }

  h = stream->strf.vids->height;
  w = stream->strf.vids->width;
  stride = GST_ROUND_UP_4 (w * (bpp / 8));

  buf = gst_buffer_make_writable (buf);
  if (GST_BUFFER_SIZE (buf) < (stride * h)) {
    GST_WARNING ("Buffer is smaller than reported Width x Height x Depth");
    return buf;
  }

  tmp = g_malloc (stride);

  for (y = 0; y < h / 2; y++) {
    swap_line (GST_BUFFER_DATA (buf) + stride * y,
        GST_BUFFER_DATA (buf) + stride * (h - 1 - y), tmp, stride);
  }

  g_free (tmp);

  return buf;
}
