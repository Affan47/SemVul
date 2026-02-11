gst_gdk_pixbuf_dec_chain (GstPad * pad, GstObject * parent, GstBuffer * buf)
{
  GstGdkPixbufDec *filter;
  GstFlowReturn ret = GST_FLOW_OK;
  GError *error = NULL;
  GstClockTime timestamp;
  GstMapInfo map;

  filter = GST_GDK_PIXBUF_DEC (parent);

  timestamp = GST_BUFFER_TIMESTAMP (buf);

  if (GST_CLOCK_TIME_IS_VALID (timestamp))
    filter->last_timestamp = timestamp;

  GST_LOG_OBJECT (filter, "buffer with ts: %" GST_TIME_FORMAT,
      GST_TIME_ARGS (timestamp));

  if (filter->pixbuf_loader == NULL)
    filter->pixbuf_loader = gdk_pixbuf_loader_new ();

  gst_buffer_map (buf, &map, GST_MAP_READ);

  GST_LOG_OBJECT (filter, "Writing buffer size %d", (gint) map.size);
  if (!gdk_pixbuf_loader_write (filter->pixbuf_loader, map.data, map.size,
          &error))
    goto error;


  if (filter->in_fps_n != 0) {
    gdk_pixbuf_loader_close (filter->pixbuf_loader, NULL);
    ret = gst_gdk_pixbuf_dec_flush (filter);
    g_object_unref (filter->pixbuf_loader);
    filter->pixbuf_loader = NULL;
  }

  gst_buffer_unmap (buf, &map);
  gst_buffer_unref (buf);

  return ret;


error:
  {
    GST_ELEMENT_ERROR (filter, STREAM, DECODE, (NULL),
        ("gdk_pixbuf_loader_write error: %s", error->message));
    g_error_free (error);
    gst_buffer_unmap (buf, &map);
    gst_buffer_unref (buf);
    return GST_FLOW_ERROR;
  }
}
