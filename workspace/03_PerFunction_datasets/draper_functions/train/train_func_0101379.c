impl_DataCalView_start (EGdbusCalView *object,
                        GDBusMethodInvocation *invocation,
                        EDataCalView *view)
{
	if (!view->priv->started) {
		GThread *thread;

		view->priv->started = TRUE;
		e_debug_log (
			FALSE, E_DEBUG_LOG_DOMAIN_CAL_QUERIES,
			"---;%p;VIEW-START;%s;%s", view,
			e_cal_backend_sexp_text (view->priv->sexp),
			G_OBJECT_TYPE_NAME (view->priv->backend));

		thread = g_thread_new (
			NULL, calview_start_thread, g_object_ref (view));
		g_thread_unref (thread);
	}

	e_gdbus_cal_view_complete_start (object, invocation, NULL);

	return TRUE;
}
