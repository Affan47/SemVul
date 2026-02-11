fv_text_handle_get_property (GObject    *object,
                             guint       prop_id,
                             GValue     *value,
                             GParamSpec *pspec)
{
  FvTextHandlePrivate *priv;

  priv = FV_TEXT_HANDLE (object)->priv;

  switch (prop_id)
    {
    case PROP_PARENT:
      g_value_set_object (value, priv->parent);
      break;
    case PROP_RELATIVE_TO:
      g_value_set_object (value, priv->relative_to);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}
