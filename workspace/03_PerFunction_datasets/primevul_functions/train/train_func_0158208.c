void mono_thread_cleanup (void)
{
#if !defined(HOST_WIN32) && !defined(RUN_IN_SUBTHREAD)


	_wapi_thread_signal_self (mono_environment_exitcode_get ());
#endif

#if 0


	DeleteCriticalSection (&threads_mutex);
	DeleteCriticalSection (&interlocked_mutex);
	DeleteCriticalSection (&contexts_mutex);
	DeleteCriticalSection (&delayed_free_table_mutex);
	DeleteCriticalSection (&small_id_mutex);
	CloseHandle (background_change_event);
#endif

	TlsFree (current_object_key);
}
