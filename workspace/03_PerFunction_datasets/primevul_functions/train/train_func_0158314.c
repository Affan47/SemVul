ves_icall_System_Threading_Thread_Abort (MonoInternalThread *thread, MonoObject *state)
{
	ensure_synch_cs_set (thread);

	EnterCriticalSection (thread->synch_cs);

	if ((thread->state & ThreadState_AbortRequested) != 0 ||
		(thread->state & ThreadState_StopRequested) != 0 ||
		(thread->state & ThreadState_Stopped) != 0)
	{
		LeaveCriticalSection (thread->synch_cs);
		return;
	}

	if ((thread->state & ThreadState_Unstarted) != 0) {
		thread->state |= ThreadState_Aborted;
		LeaveCriticalSection (thread->synch_cs);
		return;
	}

	thread->state |= ThreadState_AbortRequested;
	if (thread->abort_state_handle)
		mono_gchandle_free (thread->abort_state_handle);
	if (state) {
		thread->abort_state_handle = mono_gchandle_new (state, FALSE);
		g_assert (thread->abort_state_handle);
	} else {
		thread->abort_state_handle = 0;
	}
	thread->abort_exc = NULL;


	LeaveCriticalSection (thread->synch_cs);

	THREAD_DEBUG (g_message ("%s: (%"G_GSIZE_FORMAT") Abort requested for %p (%"G_GSIZE_FORMAT")", __func__, GetCurrentThreadId (), thread, (gsize)thread->tid));


	if (!shutting_down)

		mono_thread_resume (thread);

	signal_thread_state_change (thread);
}
