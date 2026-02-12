static void signal_thread_state_change (MonoInternalThread *thread)
{
	if (thread == mono_thread_internal_current ()) {

		MonoException *exc = mono_thread_request_interruption (FALSE);
		if (exc)
			mono_raise_exception (exc);
	}

#ifdef HOST_WIN32
	QueueUserAPC ((PAPCFUNC)interruption_request_apc, thread->handle, NULL);
#else

	mono_thread_kill (thread, mono_thread_get_abort_signal ());


	wapi_interrupt_thread (thread->handle);
#endif
}
