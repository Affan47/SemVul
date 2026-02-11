mono_thread_internal_stop (MonoInternalThread *thread)
{
	LOCK_THREAD (thread);

	if ((thread->state & ThreadState_StopRequested) != 0 ||
		(thread->state & ThreadState_Stopped) != 0)
	{
		UNLOCK_THREAD (thread);
		return;
	}


	mono_thread_resume (thread);

	thread->state |= ThreadState_StopRequested;
	thread->state &= ~ThreadState_AbortRequested;

	UNLOCK_THREAD (thread);

	abort_thread_internal (thread, TRUE, TRUE);
}
