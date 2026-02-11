class_add_super_classes_from_db (TrackerDBInterface *iface,
                                 TrackerClass       *class)
{
	TrackerDBStatement *stmt;
	TrackerDBCursor *cursor;
	GError *error = NULL;

	stmt = tracker_db_interface_create_statement (iface, TRACKER_DB_STATEMENT_CACHE_TYPE_SELECT, &error,
	                                              "SELECT (SELECT Uri FROM Resource WHERE ID = \"rdfs:subClassOf\") "
	                                              "FROM \"rdfs:Class_rdfs:subClassOf\" "
	                                              "WHERE ID = (SELECT ID FROM Resource WHERE Uri = ?)");

	if (!stmt) {
		g_critical ("%s", error->message);
		g_error_free (error);
		return;
	}

	tracker_db_statement_bind_text (stmt, 0, tracker_class_get_uri (class));
	cursor = tracker_db_statement_start_cursor (stmt, NULL);
	g_object_unref (stmt);

	if (cursor) {
		while (tracker_db_cursor_iter_next (cursor, NULL, NULL)) {
			TrackerClass *super_class;
			const gchar *super_class_uri;

			super_class_uri = tracker_db_cursor_get_string (cursor, 0, NULL);
			super_class = tracker_ontologies_get_class_by_uri (super_class_uri);
			tracker_class_add_super_class (class, super_class);
		}

		g_object_unref (cursor);
	}
}
