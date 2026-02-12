void mono_thread_suspend_all_other_threads (void)
{
	struct wait_data wait_data;
	struct wait_data *wait = &wait_data;
	int i;
	gsize self = GetCurrentThreadId ();
	gpointer *events;
	guint32 eventidx = 0;
	gboolean starting, finished;

	memset (wait, 0, sizeof (struct wait_data));


	g_assert (shutting_down);


	finished = FALSE;
	while (!finished) {


		wait->num = 0;

		memset (wait->threads, 0, MAXIMUM_WAIT_OBJECTS * SIZEOF_VOID_P);
		mono_threads_lock ();
		mono_g_hash_table_foreach (threads, collect_threads_for_suspend, wait);
		mono_threads_unlock ();

		events = g_new0 (gpointer, wait->num);
		eventidx = 0;

		for (i = 0; i < wait->num; ++i) {
			MonoInternalThread *thread = wait->threads [i];
			gboolean signal_suspend = FALSE;

			if ((thread->tid == self) || mono_gc_is_finalizer_internal_thread (thread) || (thread->flags & MONO_THREAD_FLAG_DONT_MANAGE)) {

				wait->threads [i] = NULL;
				continue;
			}

			ensure_synch_cs_set (thread);

			EnterCriticalSection (thread->synch_cs);

			if (thread->suspended_event == NULL) {
				thread->suspended_event = CreateEvent (NULL, TRUE, FALSE, NULL);
				if (thread->suspended_event == NULL) {

					LeaveCriticalSection (thread->synch_cs);
					continue;
				}
			}

			if ((thread->state & ThreadState_Suspended) != 0 ||
				(thread->state & ThreadState_StopRequested) != 0 ||
				(thread->state & ThreadState_Stopped) != 0) {
				LeaveCriticalSection (thread->synch_cs);
				CloseHandle (wait->handles [i]);
				wait->threads [i] = NULL;
				continue;
			}

			if ((thread->state & ThreadState_SuspendRequested) == 0)
				signal_suspend = TRUE;

			events [eventidx++] = thread->suspended_event;


			if ((thread->state & ThreadState_AbortRequested) != 0)
				thread->state &= ~ThreadState_AbortRequested;

			thread->state |= ThreadState_SuspendRequested;

			LeaveCriticalSection (thread->synch_cs);


			if (signal_suspend)
				signal_thread_state_change (thread);
		}

		if (eventidx > 0) {
			WaitForMultipleObjectsEx (eventidx, events, TRUE, 100, FALSE);
			for (i = 0; i < wait->num; ++i) {
				MonoInternalThread *thread = wait->threads [i];

				if (thread == NULL)
					continue;

				ensure_synch_cs_set (thread);

				EnterCriticalSection (thread->synch_cs);
				if ((thread->state & ThreadState_Suspended) != 0) {
					CloseHandle (thread->suspended_event);
					thread->suspended_event = NULL;
				}
				LeaveCriticalSection (thread->synch_cs);
			}
		} else {


			mono_threads_lock ();
			if (threads_starting_up)
				starting = mono_g_hash_table_size (threads_starting_up) > 0;
			else
				starting = FALSE;
			mono_threads_unlock ();
			if (starting)
				Sleep (100);
			else
				finished = TRUE;
		}

		g_free (events);
	}
}
