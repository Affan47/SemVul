tp_contact_get_property (GObject *object,
                         guint property_id,
                         GValue *value,
                         GParamSpec *pspec)
{
  TpContact *self = TP_CONTACT (object);

  switch (property_id)
    {
    case PROP_CONNECTION:
      g_value_set_object (value, self->priv->connection);
      break;

    case PROP_HANDLE:
      g_value_set_uint (value, self->priv->handle);
      break;

    case PROP_IDENTIFIER:
      g_assert (self->priv->identifier != NULL);
      g_value_set_string (value, self->priv->identifier);
      break;

    case PROP_ALIAS:


      g_value_set_string (value, tp_contact_get_alias (self));
      break;

    case PROP_AVATAR_TOKEN:
      g_value_set_string (value, self->priv->avatar_token);
      break;

    case PROP_AVATAR_FILE:
      g_value_set_object (value, self->priv->avatar_file);
      break;

    case PROP_AVATAR_MIME_TYPE:
      g_value_set_string (value, self->priv->avatar_mime_type);
      break;

    case PROP_PRESENCE_TYPE:
      g_value_set_uint (value, self->priv->presence_type);
      break;

    case PROP_PRESENCE_STATUS:
      g_value_set_string (value, tp_contact_get_presence_status (self));
      break;

    case PROP_PRESENCE_MESSAGE:
      g_value_set_string (value, tp_contact_get_presence_message (self));
      break;

    case PROP_LOCATION:
      g_value_set_boxed (value, tp_contact_get_location (self));
      break;

    case PROP_LOCATION_VARDICT:
      g_value_take_variant (value, tp_contact_dup_location (self));
      break;

    case PROP_CAPABILITIES:
      g_value_set_object (value, tp_contact_get_capabilities (self));
      break;

    case PROP_CONTACT_INFO:
      g_value_set_boxed (value, self->priv->contact_info);
      break;

    case PROP_CLIENT_TYPES:
      g_value_set_boxed (value, tp_contact_get_client_types (self));
      break;

    case PROP_SUBSCRIBE_STATE:
      g_value_set_uint (value, tp_contact_get_subscribe_state (self));
      break;

    case PROP_PUBLISH_STATE:
      g_value_set_uint (value, tp_contact_get_publish_state (self));
      break;

    case PROP_PUBLISH_REQUEST:
      g_value_set_string (value, tp_contact_get_publish_request (self));
      break;

    case PROP_CONTACT_GROUPS:
      g_value_set_boxed (value, tp_contact_get_contact_groups (self));
      break;

    case PROP_IS_BLOCKED:
      g_value_set_boolean (value, tp_contact_is_blocked (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}
