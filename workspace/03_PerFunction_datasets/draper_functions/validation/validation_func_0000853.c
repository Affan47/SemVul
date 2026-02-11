gst_qt_moov_recover_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec)
{
  GstQTMoovRecover *qtmr = GST_QT_MOOV_RECOVER_CAST (object);

  GST_OBJECT_LOCK (qtmr);
  switch (prop_id) {
    case PROP_FAST_START_MODE:
      qtmr->faststart_mode = g_value_get_boolean (value);
      break;
    case PROP_BROKEN_INPUT:
      g_free (qtmr->broken_input);
      qtmr->broken_input = g_value_dup_string (value);
      break;
    case PROP_RECOVERY_INPUT:
      g_free (qtmr->recovery_input);
      qtmr->recovery_input = g_value_dup_string (value);
      break;
    case PROP_FIXED_OUTPUT:
      g_free (qtmr->fixed_output);
      qtmr->fixed_output = g_value_dup_string (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
  GST_OBJECT_UNLOCK (qtmr);
}
