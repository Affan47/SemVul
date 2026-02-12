mono_threads_set_shutting_down (void)
{
	MonoInternalThread *current_thread = mono_thread_internal_current ();

	mono_threads_lock ();

	if (shutting_down) {
		mono_threads_unlock ();


		EnterCriticalSection (current_thread->synch_cs);

		if ((current_thread->state & ThreadState_SuspendRequested) ||
		    (current_thread->state & ThreadState_AbortRequested) ||
		    (current_thread->state & ThreadState_StopRequested)) {
			LeaveCriticalSection (current_thread->synch_cs);
			mono_thread_execute_interruption (current_thread);
		} else {
			current_thread->state |= ThreadState_Stopped;
			LeaveCriticalSection (current_thread->synch_cs);
		}


		mono_domain_unset ();


		ExitThread (0);
	} else {
		shutting_down = TRUE;


		SetEvent (background_change_event);

		mono_threads_unlock ();
	}
}
