tp_base_media_call_stream_get_property (GObject *object,
    guint property_id,
    GValue *value,
    GParamSpec *pspec)
{
  TpBaseMediaCallStream *self = TP_BASE_MEDIA_CALL_STREAM (object);

  switch (property_id)
    {
      case PROP_SENDING_STATE:
        g_value_set_uint (value, self->priv->sending_state);
        break;
      case PROP_RECEIVING_STATE:
        g_value_set_uint (value, self->priv->receiving_state);
        break;
      case PROP_TRANSPORT:
        g_value_set_uint (value, self->priv->transport);
        break;
      case PROP_LOCAL_CANDIDATES:
        g_value_set_boxed (value, self->priv->local_candidates);
        break;
      case PROP_LOCAL_CREDENTIALS:
        {
          g_value_take_boxed (value, tp_value_array_build (2,
              G_TYPE_STRING, self->priv->username,
              G_TYPE_STRING, self->priv->password,
              G_TYPE_INVALID));
          break;
        }
      case PROP_STUN_SERVERS:
        {
          if (self->priv->stun_servers != NULL)
            g_value_set_boxed (value, self->priv->stun_servers);
          else
            g_value_take_boxed (value, g_ptr_array_new ());
          break;
        }
      case PROP_RELAY_INFO:
        {
          if (self->priv->relay_info != NULL)
            g_value_set_boxed (value, self->priv->relay_info);
          else
            g_value_take_boxed (value, g_ptr_array_new ());
          break;
        }
      case PROP_HAS_SERVER_INFO:
        g_value_set_boolean (value, self->priv->has_server_info);
        break;
      case PROP_ENDPOINTS:
        {
          GPtrArray *arr = g_ptr_array_sized_new (1);
          GList *l;

          for (l = self->priv->endpoints; l != NULL; l = g_list_next (l))
            {
              TpCallStreamEndpoint *e = l->data;

              g_ptr_array_add (arr,
                  g_strdup (tp_call_stream_endpoint_get_object_path (e)));
            }

          g_value_take_boxed (value, arr);
          break;
        }
      case PROP_ICE_RESTART_PENDING:
        g_value_set_boolean (value, self->priv->ice_restart_pending);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}
