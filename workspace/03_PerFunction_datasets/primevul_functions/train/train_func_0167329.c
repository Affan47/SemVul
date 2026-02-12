real_parse_error_response (GDataService *self, GDataOperationType operation_type, guint status, const gchar *reason_phrase,
                           const gchar *response_body, gint length, GError **error)
{

	if (response_body == NULL || *response_body == '\0')
		response_body = reason_phrase;


	switch (status) {
		case SOUP_STATUS_CANT_RESOLVE:
		case SOUP_STATUS_CANT_CONNECT:
		case SOUP_STATUS_SSL_FAILED:
		case SOUP_STATUS_IO_ERROR:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_NETWORK_ERROR,
			             _("Cannot connect to the service's server."));
			return;
		case SOUP_STATUS_CANT_RESOLVE_PROXY:
		case SOUP_STATUS_CANT_CONNECT_PROXY:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_PROXY_ERROR,
			             _("Cannot connect to the proxy server."));
			return;
		case SOUP_STATUS_MALFORMED:
		case SOUP_STATUS_BAD_REQUEST:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_PROTOCOL_ERROR,

			             _("Invalid request URI or header, or unsupported nonstandard parameter: %s"), response_body);
			return;
		case SOUP_STATUS_UNAUTHORIZED:
		case SOUP_STATUS_FORBIDDEN:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_AUTHENTICATION_REQUIRED,

			             _("Authentication required: %s"), response_body);
			return;
		case SOUP_STATUS_NOT_FOUND:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_NOT_FOUND,

			             _("The requested resource was not found: %s"), response_body);
			return;
		case SOUP_STATUS_CONFLICT:
		case SOUP_STATUS_PRECONDITION_FAILED:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_CONFLICT,

			             _("The entry has been modified since it was downloaded: %s"), response_body);
			return;
		case SOUP_STATUS_INTERNAL_SERVER_ERROR:
		default:

			break;
	}


	switch (operation_type) {
		case GDATA_OPERATION_AUTHENTICATION:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_PROTOCOL_ERROR,


			             _("Error code %u when authenticating: %s"), status, response_body);
			break;
		case GDATA_OPERATION_QUERY:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_PROTOCOL_ERROR,


			             _("Error code %u when querying: %s"), status, response_body);
			break;
		case GDATA_OPERATION_INSERTION:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_PROTOCOL_ERROR,


			             _("Error code %u when inserting an entry: %s"), status, response_body);
			break;
		case GDATA_OPERATION_UPDATE:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_PROTOCOL_ERROR,


			             _("Error code %u when updating an entry: %s"), status, response_body);
			break;
		case GDATA_OPERATION_DELETION:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_PROTOCOL_ERROR,


			             _("Error code %u when deleting an entry: %s"), status, response_body);
			break;
		case GDATA_OPERATION_DOWNLOAD:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_PROTOCOL_ERROR,


			             _("Error code %u when downloading: %s"), status, response_body);
			break;
		case GDATA_OPERATION_UPLOAD:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_PROTOCOL_ERROR,


			             _("Error code %u when uploading: %s"), status, response_body);
			break;
		case GDATA_OPERATION_BATCH:
			g_set_error (error, GDATA_SERVICE_ERROR, GDATA_SERVICE_ERROR_WITH_BATCH_OPERATION,


			             _("Error code %u when running a batch operation: %s"), status, response_body);
			break;
		default:

			g_assert_not_reached ();
	}
}
