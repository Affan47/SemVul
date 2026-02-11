gst_video_mark_yuv (GstVideoMark * videomark, GstBuffer * buffer)
{
  GstVideoFormat format;
  gint i, pw, ph, row_stride, pixel_stride, offset;
  gint width, height, req_width, req_height;
  guint8 *d, *data;
  guint64 pattern_shift;
  guint8 color;

  data = GST_BUFFER_DATA (buffer);

  format = videomark->format;
  width = videomark->width;
  height = videomark->height;

  pw = videomark->pattern_width;
  ph = videomark->pattern_height;
  row_stride = gst_video_format_get_row_stride (format, 0, width);
  pixel_stride = gst_video_format_get_pixel_stride (format, 0);
  offset = gst_video_format_get_component_offset (format, 0, width, height);

  req_width =
      (videomark->pattern_count + videomark->pattern_data_count) * pw +
      videomark->left_offset;
  req_height = videomark->bottom_offset + ph;
  if (req_width > width || req_height > height) {
    GST_ELEMENT_ERROR (videomark, STREAM, WRONG_TYPE, (NULL),
        ("videomark pattern doesn't fit video, need at least %ix%i (stream has %ix%i)",
            req_width, req_height, width, height));
    return GST_FLOW_ERROR;
  }


  for (i = 0; i < videomark->pattern_count; i++) {
    d = data + offset;

    d += row_stride * (height - ph - videomark->bottom_offset) +
        pixel_stride * videomark->left_offset;

    d += pixel_stride * pw * i;

    if (i & 1)

      color = 255;
    else
      color = 0;


    gst_video_mark_draw_box (videomark, d, pw, ph, row_stride, pixel_stride,
        color);
  }

  pattern_shift = G_GUINT64_CONSTANT (1) << (videomark->pattern_data_count - 1);


  for (i = 0; i < videomark->pattern_data_count; i++) {
    d = data + offset;

    d += row_stride * (height - ph - videomark->bottom_offset) +
        pixel_stride * videomark->left_offset;

    d += pixel_stride * videomark->pattern_count * pw;

    d += pixel_stride * pw * i;

    if (videomark->pattern_data & pattern_shift)
      color = 255;
    else
      color = 0;

    gst_video_mark_draw_box (videomark, d, pw, ph, row_stride, pixel_stride,
        color);

    pattern_shift >>= 1;
  }

  return GST_FLOW_OK;
}
