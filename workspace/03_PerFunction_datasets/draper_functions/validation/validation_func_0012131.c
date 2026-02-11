goo_canvas_group_set_common_property (GObject               *object,
                                      GooCanvasGroupPrivate *priv,
                                      guint                  prop_id,
                                      const GValue          *value,
                                      GParamSpec            *pspec)
{
  switch (prop_id)
    {
    case PROP_X:
      priv->x = g_value_get_double (value);
      break;
    case PROP_Y:
      priv->y = g_value_get_double (value);
      break;
    case PROP_WIDTH:
      priv->width = g_value_get_double (value);
      break;
    case PROP_HEIGHT:
      priv->height = g_value_get_double (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
