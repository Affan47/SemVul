event_reset (gpointer handle)
{
	struct _WapiHandle_event *event_handle;
	gboolean ok;
	int thr_ret;

	ok = _wapi_lookup_handle (handle, WAPI_HANDLE_EVENT,
				  (gpointer *)&event_handle);
	if (ok == FALSE) {
		g_warning ("%s: error looking up event handle %p",
			   __func__, handle);
		return(FALSE);
	}

	DEBUG ("%s: Resetting event handle %p", __func__, handle);

	thr_ret = _wapi_handle_lock_handle (handle);
	g_assert (thr_ret == 0);

	if (_wapi_handle_issignalled (handle) == FALSE) {
		DEBUG ("%s: No need to reset event handle %p", __func__,
			   handle);
	} else {
		DEBUG ("%s: Obtained write lock on event handle %p",
			   __func__, handle);

		_wapi_handle_set_signal_state (handle, FALSE, FALSE);
	}

	event_handle->set_count = 0;

	thr_ret = _wapi_handle_unlock_handle (handle);
	g_assert (thr_ret == 0);

	return(TRUE);
}
