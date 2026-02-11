gst_stream_selector_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstStreamSelector *sel = GST_STREAM_SELECTOR (object);

  switch (prop_id) {
    case PROP_N_PADS:
      GST_OBJECT_LOCK (object);
      g_value_set_uint (value, sel->n_pads);
      GST_OBJECT_UNLOCK (object);
      break;
    case PROP_ACTIVE_PAD:{
      GST_OBJECT_LOCK (object);
      g_value_set_object (value, sel->active_sinkpad);
      GST_OBJECT_UNLOCK (object);
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
