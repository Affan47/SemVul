gst_video_overlay_rectangle_finalize (GstMiniObject * mini_obj)
{
  GstVideoOverlayRectangle *rect = (GstVideoOverlayRectangle *) mini_obj;

  gst_buffer_replace (&rect->pixels, NULL);

  while (rect->scaled_rectangles != NULL) {
    GstVideoOverlayRectangle *scaled_rect = rect->scaled_rectangles->data;

    gst_video_overlay_rectangle_unref (scaled_rect);

    rect->scaled_rectangles =
        g_list_delete_link (rect->scaled_rectangles, rect->scaled_rectangles);
  }
#if !GLIB_CHECK_VERSION (2, 31, 0)
  g_static_mutex_free (&rect->lock);
#else
  g_mutex_clear (&rect->lock);
#endif

}
