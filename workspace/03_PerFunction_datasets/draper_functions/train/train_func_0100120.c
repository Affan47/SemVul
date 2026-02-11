folder_emit_deleted_cb (gpointer user_data)
{
	SignalClosure *signal_closure = user_data;
	CamelFolder *folder;

	folder = g_weak_ref_get (&signal_closure->folder);

	if (folder != NULL) {
		g_signal_emit (folder, signals[DELETED], 0);
		g_object_unref (folder);
	}

	return FALSE;
}
