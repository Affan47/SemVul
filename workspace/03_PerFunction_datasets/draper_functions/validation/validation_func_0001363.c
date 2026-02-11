gst_qt_mux_get_property (GObject * object,
    guint prop_id, GValue * value, GParamSpec * pspec)
{
  GstQTMux *qtmux = GST_QT_MUX_CAST (object);

  GST_OBJECT_LOCK (qtmux);
  switch (prop_id) {
    case PROP_MOVIE_TIMESCALE:
      g_value_set_uint (value, qtmux->timescale);
      break;
    case PROP_TRAK_TIMESCALE:
      g_value_set_uint (value, qtmux->trak_timescale);
      break;
    case PROP_DO_CTTS:
      g_value_set_boolean (value, qtmux->guess_pts);
      break;
    case PROP_DTS_METHOD:
      g_value_set_enum (value, qtmux->dts_method);
      break;
    case PROP_FAST_START:
      g_value_set_boolean (value, qtmux->fast_start);
      break;
    case PROP_FAST_START_TEMP_FILE:
      g_value_set_string (value, qtmux->fast_start_file_path);
      break;
    case PROP_MOOV_RECOV_FILE:
      g_value_set_string (value, qtmux->moov_recov_file_path);
      break;
    case PROP_FRAGMENT_DURATION:
      g_value_set_uint (value, qtmux->fragment_duration);
      break;
    case PROP_STREAMABLE:
      g_value_set_boolean (value, qtmux->streamable);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
  GST_OBJECT_UNLOCK (qtmux);
}
