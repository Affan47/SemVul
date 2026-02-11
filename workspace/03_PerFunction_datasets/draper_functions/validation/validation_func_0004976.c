gst_vcdsrc_set_property (GObject * object, guint prop_id, const GValue * value,
    GParamSpec * pspec)
{
  GstVCDSrc *src;

  src = GST_VCDSRC (object);

  switch (prop_id) {
    case PROP_DEVICE:
      g_free (src->device);
      src->device = g_value_dup_string (value);
      break;
    case PROP_TRACK:
      if (g_value_get_int (value) >= 1 &&
          g_value_get_int (value) < src->numtracks) {
        src->track = g_value_get_int (value);
        gst_vcdsrc_recalculate (src);
      }
      break;
    case PROP_MAX_ERRORS:
      src->max_errors = g_value_get_int (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
