real_append_query_headers (GDataService *self, GDataAuthorizationDomain *domain, SoupMessage *message)
{
	g_assert (message != NULL);


	if (self->priv->authorizer != NULL) {
		gdata_authorizer_process_request (self->priv->authorizer, domain, message);

		if (domain != NULL) {


			g_object_set_data_full (G_OBJECT (message), "gdata-authorization-domain", g_object_ref (domain),
			                        (GDestroyNotify) g_object_unref);
		}
	}


	soup_message_headers_append (message->request_headers, "GData-Version", GDATA_SERVICE_GET_CLASS (self)->api_version);


	if (self->priv->locale != NULL)
		soup_message_headers_append (message->request_headers, "Accept-Language", self->priv->locale);
}
