gst_discoverer_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstDiscoverer *dc = (GstDiscoverer *) object;

  switch (prop_id) {
    case PROP_TIMEOUT:
      DISCO_LOCK (dc);
      g_value_set_uint64 (value, dc->priv->timeout);
      DISCO_UNLOCK (dc);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
