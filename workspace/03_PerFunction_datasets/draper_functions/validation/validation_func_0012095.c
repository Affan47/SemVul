_wapi_thread_apc_pending (gpointer handle)
{
	struct _WapiHandle_thread *thread;
	gboolean ok;

	ok = _wapi_lookup_handle (handle, WAPI_HANDLE_THREAD,
				  (gpointer *)&thread);
	if (ok == FALSE) {


		DEBUG ("%s: error looking up thread handle %p", __func__,
			   handle);
		return (FALSE);
	}

	return(thread->has_apc || thread->wait_handle == INTERRUPTION_REQUESTED_HANDLE);
}
