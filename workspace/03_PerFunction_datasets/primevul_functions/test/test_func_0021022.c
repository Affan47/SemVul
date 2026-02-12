g_socket_client_class_init (GSocketClientClass *class)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (class);

  gobject_class->finalize = g_socket_client_finalize;
  gobject_class->set_property = g_socket_client_set_property;
  gobject_class->get_property = g_socket_client_get_property;


  signals[EVENT] =
    g_signal_new (I_("event"),
		  G_TYPE_FROM_CLASS (gobject_class),
		  G_SIGNAL_RUN_LAST,
		  G_STRUCT_OFFSET (GSocketClientClass, event),
		  NULL, NULL,
		  NULL,
		  G_TYPE_NONE, 3,
		  G_TYPE_SOCKET_CLIENT_EVENT,
		  G_TYPE_SOCKET_CONNECTABLE,
		  G_TYPE_IO_STREAM);

  g_object_class_install_property (gobject_class, PROP_FAMILY,
				   g_param_spec_enum ("family",
						      P_("Socket family"),
						      P_("The sockets address family to use for socket construction"),
						      G_TYPE_SOCKET_FAMILY,
						      G_SOCKET_FAMILY_INVALID,
						      G_PARAM_CONSTRUCT |
                                                      G_PARAM_READWRITE |
                                                      G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_TYPE,
				   g_param_spec_enum ("type",
						      P_("Socket type"),
						      P_("The sockets type to use for socket construction"),
						      G_TYPE_SOCKET_TYPE,
						      G_SOCKET_TYPE_STREAM,
						      G_PARAM_CONSTRUCT |
                                                      G_PARAM_READWRITE |
                                                      G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_PROTOCOL,
				   g_param_spec_enum ("protocol",
						      P_("Socket protocol"),
						      P_("The protocol to use for socket construction, or 0 for default"),
						      G_TYPE_SOCKET_PROTOCOL,
						      G_SOCKET_PROTOCOL_DEFAULT,
						      G_PARAM_CONSTRUCT |
                                                      G_PARAM_READWRITE |
                                                      G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_LOCAL_ADDRESS,
				   g_param_spec_object ("local-address",
							P_("Local address"),
							P_("The local address constructed sockets will be bound to"),
							G_TYPE_SOCKET_ADDRESS,
							G_PARAM_CONSTRUCT |
                                                        G_PARAM_READWRITE |
                                                        G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_TIMEOUT,
				   g_param_spec_uint ("timeout",
						      P_("Socket timeout"),
						      P_("The I/O timeout for sockets, or 0 for none"),
						      0, G_MAXUINT, 0,
						      G_PARAM_CONSTRUCT |
                                                      G_PARAM_READWRITE |
                                                      G_PARAM_STATIC_STRINGS));

   g_object_class_install_property (gobject_class, PROP_ENABLE_PROXY,
				    g_param_spec_boolean ("enable-proxy",
							  P_("Enable proxy"),
							  P_("Enable proxy support"),
							  TRUE,
							  G_PARAM_CONSTRUCT |
							  G_PARAM_READWRITE |
							  G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_TLS,
				   g_param_spec_boolean ("tls",
							 P_("TLS"),
							 P_("Whether to create TLS connections"),
							 FALSE,
							 G_PARAM_CONSTRUCT |
							 G_PARAM_READWRITE |
							 G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (gobject_class, PROP_TLS_VALIDATION_FLAGS,
				   g_param_spec_flags ("tls-validation-flags",
						       P_("TLS validation flags"),
						       P_("TLS validation flags to use"),
						       G_TYPE_TLS_CERTIFICATE_FLAGS,
						       G_TLS_CERTIFICATE_VALIDATE_ALL,
						       G_PARAM_CONSTRUCT |
						       G_PARAM_READWRITE |
						       G_PARAM_STATIC_STRINGS));


  g_object_class_install_property (gobject_class, PROP_PROXY_RESOLVER,
                                   g_param_spec_object ("proxy-resolver",
                                                        P_("Proxy resolver"),
                                                        P_("The proxy resolver to use"),
                                                        G_TYPE_PROXY_RESOLVER,
                                                        G_PARAM_CONSTRUCT |
                                                        G_PARAM_READWRITE |
                                                        G_PARAM_STATIC_STRINGS));
}
