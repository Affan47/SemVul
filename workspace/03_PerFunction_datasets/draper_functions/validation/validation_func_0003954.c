glade_property_get_real_property (GObject * object,
                                  guint prop_id,
                                  GValue * value, GParamSpec * pspec)
{
  GladeProperty *property = GLADE_PROPERTY (object);

  switch (prop_id)
    {
      case PROP_CLASS:
        g_value_set_pointer (value, property->priv->klass);
        break;
      case PROP_ENABLED:
        g_value_set_boolean (value, glade_property_get_enabled (property));
        break;
      case PROP_SENSITIVE:
        g_value_set_boolean (value, glade_property_get_sensitive (property));
        break;
      case PROP_I18N_TRANSLATABLE:
        g_value_set_boolean (value,
                             glade_property_i18n_get_translatable (property));
        break;
      case PROP_I18N_CONTEXT:
        g_value_set_string (value, glade_property_i18n_get_context (property));
        break;
      case PROP_I18N_COMMENT:
        g_value_set_string (value, glade_property_i18n_get_comment (property));
        break;
      case PROP_STATE:
        g_value_set_int (value, property->priv->state);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}
