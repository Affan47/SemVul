_gdata_service_query (GDataService *self, GDataAuthorizationDomain *domain, const gchar *feed_uri, GDataQuery *query,
                      GCancellable *cancellable, GError **error)
{
	SoupMessage *message;
	guint status;
	const gchar *etag = NULL;


	if (query != NULL)
		etag = gdata_query_get_etag (query);


	if (query != NULL) {
		gchar *query_uri = gdata_query_get_query_uri (query, feed_uri);
		message = _gdata_service_build_message (self, domain, SOUP_METHOD_GET, query_uri, etag, FALSE);
		g_free (query_uri);
	} else {
		message = _gdata_service_build_message (self, domain, SOUP_METHOD_GET, feed_uri, etag, FALSE);
	}


	status = _gdata_service_send_message (self, message, cancellable, error);

	if (status == SOUP_STATUS_NOT_MODIFIED || status == SOUP_STATUS_CANCELLED) {

		g_object_unref (message);
		return NULL;
	} else if (status != SOUP_STATUS_OK) {

		GDataServiceClass *klass = GDATA_SERVICE_GET_CLASS (self);
		g_assert (klass->parse_error_response != NULL);
		klass->parse_error_response (self, GDATA_OPERATION_QUERY, status, message->reason_phrase, message->response_body->data,
		                             message->response_body->length, error);
		g_object_unref (message);
		return NULL;
	}

	return message;
}
