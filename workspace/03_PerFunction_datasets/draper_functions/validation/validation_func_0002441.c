gst_wrapper_camera_bin_src_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec)
{
  GstWrapperCameraBinSrc *self = GST_WRAPPER_CAMERA_BIN_SRC (object);

  switch (prop_id) {
    case PROP_VIDEO_SRC:
      if (GST_STATE (self) != GST_STATE_NULL) {
        GST_ELEMENT_ERROR (self, CORE, FAILED,
            ("camerasrc must be in NULL state when setting the video source element"),
            (NULL));
      } else {
        if (self->app_vid_src)
          gst_object_unref (self->app_vid_src);
        self->app_vid_src = g_value_get_object (value);
        if (self->app_vid_src)
          gst_object_ref (self->app_vid_src);
      }
      break;
    case PROP_VIDEO_SRC_FILTER:
      if (GST_STATE (self) != GST_STATE_NULL) {
        GST_ELEMENT_ERROR (self, CORE, FAILED,
            ("camerasrc must be in NULL state when setting the video source filter element"),
            (NULL));
      } else {
        if (self->app_vid_filter)
          gst_object_unref (self->app_vid_filter);
        self->app_vid_filter = g_value_get_object (value);
        if (self->app_vid_filter)
          gst_object_ref (self->app_vid_filter);
      }
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (self, prop_id, pspec);
      break;
  }
}
