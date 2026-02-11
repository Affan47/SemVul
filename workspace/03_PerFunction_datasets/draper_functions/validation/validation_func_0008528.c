query_urns_by_url (const gchar *uri)
{
	GError *error = NULL;
	TrackerSparqlCursor *cursor;
	gchar *sparql;
	gchar **urns;

	sparql = g_strdup_printf ("SELECT ?urn WHERE { ?urn nie:url \"%s\" }",
	                          uri);


	cursor = tracker_sparql_connection_query (connection,
	                                          sparql,
	                                          NULL,
	                                          &error);
	if (error) {

		g_error ("Couldn't query the Tracker Store: '%s'",
		         error ? error->message : "unknown error");
	}


	if (!cursor) {
		urns = NULL;
	} else {
		gchar *urns_mixed;
		GString *urns_string;
		gint i = 0;

		urns_string = g_string_new ("");

		while (tracker_sparql_cursor_next (cursor, NULL, &error)) {
			g_string_append_printf (urns_string,
			                        "%s%s",
			                        i==0 ? "" : ";",
			                        tracker_sparql_cursor_get_string (cursor, 0, NULL));
			i++;
		}

		if (error) {
			g_error ("Error iterating cursor: %s",
			         error->message);
		}

		urns_mixed = g_string_free (urns_string, FALSE);
		urns = g_strsplit (urns_mixed, ";", -1);
		g_free (urns_mixed);
		g_object_unref (cursor);
	}

	g_free (sparql);

	return urns;
}
