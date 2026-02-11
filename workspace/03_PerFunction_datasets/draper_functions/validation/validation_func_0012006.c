pseudo_tcp_socket_set_property (GObject *object,
                                  guint property_id,
                                  const GValue *value,
                                  GParamSpec *pspec)
{
  PseudoTcpSocket *self = PSEUDO_TCP_SOCKET (object);

  switch (property_id) {
    case PROP_CONVERSATION:
      self->priv->conv = g_value_get_uint (value);
      break;
    case PROP_CALLBACKS:
      {
        PseudoTcpCallbacks *c = g_value_get_pointer (value);
        self->priv->callbacks = *c;
      }
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}
