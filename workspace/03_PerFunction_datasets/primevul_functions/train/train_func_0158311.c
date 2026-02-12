static MonoException* mono_thread_execute_interruption (MonoInternalThread *thread)
{
	ensure_synch_cs_set (thread);

	EnterCriticalSection (thread->synch_cs);


	if (InterlockedCompareExchange (&thread->interruption_requested, FALSE, TRUE)) {

		WaitForSingleObjectEx (GetCurrentThread(), 0, TRUE);
		InterlockedDecrement (&thread_interruption_requested);
#ifndef HOST_WIN32

		wapi_clear_interruption ();
#endif
	}

	if ((thread->state & ThreadState_AbortRequested) != 0) {
		LeaveCriticalSection (thread->synch_cs);
		if (thread->abort_exc == NULL) {


			MONO_OBJECT_SETREF (thread, abort_exc, mono_get_exception_thread_abort ());
		}
		return thread->abort_exc;
	}
	else if ((thread->state & ThreadState_SuspendRequested) != 0) {
		thread->state &= ~ThreadState_SuspendRequested;
		thread->state |= ThreadState_Suspended;
		thread->suspend_event = CreateEvent (NULL, TRUE, FALSE, NULL);
		if (thread->suspend_event == NULL) {
			LeaveCriticalSection (thread->synch_cs);
			return(NULL);
		}
		if (thread->suspended_event)
			SetEvent (thread->suspended_event);

		LeaveCriticalSection (thread->synch_cs);

		if (shutting_down) {

			for (;;)
				Sleep (1000);
		}

		WaitForSingleObject (thread->suspend_event, INFINITE);

		EnterCriticalSection (thread->synch_cs);

		CloseHandle (thread->suspend_event);
		thread->suspend_event = NULL;
		thread->state &= ~ThreadState_Suspended;


		SetEvent (thread->resume_event);

		LeaveCriticalSection (thread->synch_cs);

		return NULL;
	}
	else if ((thread->state & ThreadState_StopRequested) != 0) {


		LeaveCriticalSection (thread->synch_cs);

		mono_thread_exit ();
		return NULL;
	} else if (thread->thread_interrupt_requested) {

		thread->thread_interrupt_requested = FALSE;
		LeaveCriticalSection (thread->synch_cs);

		return(mono_get_exception_thread_interrupted ());
	}

	LeaveCriticalSection (thread->synch_cs);

	return NULL;
}
