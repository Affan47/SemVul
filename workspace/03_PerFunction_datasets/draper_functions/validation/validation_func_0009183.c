data_cal_handle_get_free_busy_cb (EDBusCalendar *interface,
                                  GDBusMethodInvocation *invocation,
                                  gint64 in_start,
                                  gint64 in_end,
                                  const gchar * const *in_users,
                                  EDataCal *data_cal)
{
	ECalBackend *backend;
	AsyncContext *async_context;

	backend = e_data_cal_ref_backend (data_cal);
	g_return_val_if_fail (backend != NULL, FALSE);

	async_context = async_context_new (data_cal, invocation);

	e_cal_backend_get_free_busy (
		backend,
		(time_t) in_start,
		(time_t) in_end,
		in_users,
		async_context->cancellable,
		data_cal_complete_get_free_busy_cb,
		async_context);

	g_object_unref (backend);

	return TRUE;
}
