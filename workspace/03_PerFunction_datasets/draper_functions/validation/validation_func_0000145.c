timestamp_sort_func (GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data)
{
	NMConnection *conn_a, *conn_b;
	guint64 time_a, time_b;

	gtk_tree_model_get (model, a,
	                    COL_CONNECTION, &conn_a,
	                    COL_TIMESTAMP, &time_a,
	                    -1);
	gtk_tree_model_get (model, b,
	                    COL_CONNECTION, &conn_b,
	                    COL_TIMESTAMP, &time_b,
	                    -1);

	if (!conn_a || !conn_b) {
		g_assert (!conn_a && !conn_b);
		return sort_connection_types (model, a, b, user_data);
	}

	g_object_unref (conn_a);
	g_object_unref (conn_b);

	return time_b - time_a;
}
