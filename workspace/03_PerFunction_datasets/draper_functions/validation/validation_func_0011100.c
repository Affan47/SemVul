gst_pnmenc_set_property (GObject * object, guint prop_id, const GValue * value,
    GParamSpec * pspec)
{
  GstPnmenc *s = GST_PNMENC (object);

  switch (prop_id) {
    case GST_PNMENC_PROP_ASCII:
      if (g_value_get_boolean (value))
        s->info.encoding = GST_PNM_ENCODING_ASCII;
      else
        s->info.encoding = GST_PNM_ENCODING_RAW;
      s->info.fields |= GST_PNM_INFO_FIELDS_ENCODING;
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
