do_process_file (TrackerMinerFS *fs,
                 TrackerTask    *task)
{
	TrackerMinerFSPrivate *priv;
	gboolean processing;
	gboolean attribute_update_only;
	gchar *uri;
	GFile *task_file;
	UpdateProcessingTaskContext *ctxt;

	ctxt = tracker_task_get_data (task);
	task_file = tracker_task_get_file (task);
	uri = g_file_get_uri (task_file);
	priv = fs->priv;

	attribute_update_only = GPOINTER_TO_INT (g_object_get_qdata (G_OBJECT (task_file),
	                                                             priv->quark_attribute_updated));

	if (!attribute_update_only) {
		g_debug ("Processing file '%s'...", uri);
		g_signal_emit (fs, signals[PROCESS_FILE], 0,
		               task_file,
		               ctxt->builder,
		               ctxt->cancellable,
		               &processing);
	} else {
		g_debug ("Processing attributes in file '%s'...", uri);
		g_signal_emit (fs, signals[PROCESS_FILE_ATTRIBUTES], 0,
		               task_file,
		               ctxt->builder,
		               ctxt->cancellable,
		               &processing);
	}

	if (!processing) {


		task = tracker_task_pool_find (priv->task_pool, task_file);

		g_message ("%s refused to process '%s'", G_OBJECT_TYPE_NAME (fs), uri);

		if (!task) {
			g_critical ("%s has returned FALSE in ::process-file for '%s', "
			            "but it seems that this file has been processed through "
			            "tracker_miner_fs_file_notify(), this is an "
			            "implementation error", G_OBJECT_TYPE_NAME (fs), uri);
		} else {
			tracker_task_pool_remove (priv->task_pool, task);
			tracker_task_unref (task);
		}
	}

	g_free (uri);

	return processing;
}
