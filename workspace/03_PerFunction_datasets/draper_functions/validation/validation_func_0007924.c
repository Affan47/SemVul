net_object_set_property (GObject *object_,
                         guint prop_id,
                         const GValue *value,
                         GParamSpec *pspec)
{
        NetObject *object = NET_OBJECT (object_);
        NetObjectPrivate *priv = object->priv;

        switch (prop_id) {
        case PROP_ID:
                g_free (priv->id);
                priv->id = g_strdup (g_value_get_string (value));
                break;
        case PROP_TITLE:
                g_free (priv->title);
                priv->title = g_strdup (g_value_get_string (value));
                break;
        case PROP_REMOVABLE:
                priv->removable = g_value_get_boolean (value);
                break;
        case PROP_CLIENT:
                priv->client = g_value_dup_object (value);
                break;
        case PROP_REMOTE_SETTINGS:
                priv->remote_settings = g_value_dup_object (value);
                break;
        case PROP_CANCELLABLE:
                priv->cancellable = g_value_dup_object (value);
                break;
        case PROP_PANEL:
                priv->panel = g_value_dup_object (value);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                break;
        }
}
