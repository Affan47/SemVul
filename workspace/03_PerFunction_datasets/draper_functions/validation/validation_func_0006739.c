gst_base_src_update_length (GstBaseSrc * src, guint64 offset, guint * length)
{
  guint64 size, maxsize;
  GstBaseSrcClass *bclass;
  GstFormat format;
  gint64 stop;
  gboolean dynamic;

  bclass = GST_BASE_SRC_GET_CLASS (src);

  format = src->segment.format;
  stop = src->segment.stop;

  size = (guint64) src->segment.duration;


  if (format != GST_FORMAT_BYTES)
    return TRUE;


  if (stop != -1)
    maxsize = MIN (size, stop);
  else
    maxsize = size;

  GST_DEBUG_OBJECT (src,
      "reading offset %" G_GUINT64_FORMAT ", length %u, size %" G_GINT64_FORMAT
      ", segment.stop %" G_GINT64_FORMAT ", maxsize %" G_GINT64_FORMAT, offset,
      *length, size, stop, maxsize);

  dynamic = g_atomic_int_get (&src->priv->dynamic_size);
  GST_DEBUG_OBJECT (src, "dynamic size: %d", dynamic);


  if (maxsize != -1) {


    if (G_UNLIKELY (offset + *length >= maxsize || dynamic)) {

      if (bclass->get_size)
        if (!bclass->get_size (src, &size))
          size = -1;


      if (stop != -1)
        maxsize = MIN (size, stop);
      else
        maxsize = size;


      if (G_UNLIKELY (offset >= maxsize))
        goto unexpected_length;


      if (G_UNLIKELY (offset + *length >= maxsize))
        *length = maxsize - offset;

    }
  }


  GST_OBJECT_LOCK (src);
  gst_segment_set_duration (&src->segment, GST_FORMAT_BYTES, size);
  GST_OBJECT_UNLOCK (src);

  return TRUE;


unexpected_length:
  {
    return FALSE;
  }
}
