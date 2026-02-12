gdata_service_class_init (GDataServiceClass *klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (GDataServicePrivate));

	gobject_class->set_property = gdata_service_set_property;
	gobject_class->get_property = gdata_service_get_property;
	gobject_class->dispose = gdata_service_dispose;
	gobject_class->finalize = gdata_service_finalize;

	klass->api_version = "2";
	klass->feed_type = GDATA_TYPE_FEED;
	klass->append_query_headers = real_append_query_headers;
	klass->parse_error_response = real_parse_error_response;
	klass->get_authorization_domains = NULL;


	g_object_class_install_property (gobject_class, PROP_PROXY_URI,
	                                 g_param_spec_boxed ("proxy-uri",
	                                                     "Proxy URI", "The proxy URI used internally for all network requests.",
	                                                     SOUP_TYPE_URI,
	                                                     G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


	g_object_class_install_property (gobject_class, PROP_TIMEOUT,
	                                 g_param_spec_uint ("timeout",
	                                                    "Timeout", "A timeout, in seconds, for network operations.",
	                                                    0, G_MAXUINT, 0,
	                                                    G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


	g_object_class_install_property (gobject_class, PROP_LOCALE,
	                                 g_param_spec_string ("locale",
	                                                      "Locale", "The locale to use for network requests, in Unix locale format.",
	                                                      NULL,
	                                                      G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


	g_object_class_install_property (gobject_class, PROP_AUTHORIZER,
	                                 g_param_spec_object ("authorizer",
	                                                      "Authorizer", "An authorizer object to provide an authorization token for each request.",
	                                                      GDATA_TYPE_AUTHORIZER,
	                                                      G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
}
