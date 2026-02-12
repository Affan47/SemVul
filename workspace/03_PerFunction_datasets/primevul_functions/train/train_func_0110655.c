got_headers (SoupMessage *req, SoupClientContext *client)
{
	SoupServer *server = client->server;
	SoupServerPrivate *priv = SOUP_SERVER_GET_PRIVATE (server);
	SoupURI *uri;
	SoupDate *date;
	char *date_string;
	SoupAuthDomain *domain;
	GSList *iter;
	gboolean rejected = FALSE;
	char *auth_user;

	if (!priv->raw_paths) {
		char *decoded_path;

		uri = soup_message_get_uri (req);
		decoded_path = soup_uri_decode (uri->path);

		if (strstr (decoded_path, "/../") ||
		    g_str_has_suffix (decoded_path, "/..")) {

			g_free (decoded_path);
			soup_message_set_status (req, SOUP_STATUS_BAD_REQUEST);
			return;
		}

		soup_uri_set_path (uri, decoded_path);
		g_free (decoded_path);
	}


	date = soup_date_new_from_now (0);
	date_string = soup_date_to_string (date, SOUP_DATE_HTTP);
	soup_message_headers_replace (req->response_headers, "Date",
				      date_string);
	g_free (date_string);
	soup_date_free (date);


	for (iter = priv->auth_domains; iter; iter = iter->next) {
		domain = iter->data;

		if (soup_auth_domain_covers (domain, req)) {
			auth_user = soup_auth_domain_accepts (domain, req);
			if (auth_user) {
				client->auth_domain = g_object_ref (domain);
				client->auth_user = auth_user;
				return;
			}

			rejected = TRUE;
		}
	}


	if (!rejected)
		return;

	for (iter = priv->auth_domains; iter; iter = iter->next) {
		domain = iter->data;

		if (soup_auth_domain_covers (domain, req))
			soup_auth_domain_challenge (domain, req);
	}
}
