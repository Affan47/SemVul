void mono_thread_manage (void)
{
	struct wait_data wait_data;
	struct wait_data *wait = &wait_data;

	memset (wait, 0, sizeof (struct wait_data));

	THREAD_DEBUG (g_message ("%s: Joining each running thread...", __func__));

	mono_threads_lock ();
	if(threads==NULL) {
		THREAD_DEBUG (g_message("%s: No threads", __func__));
		mono_threads_unlock ();
		return;
	}
	mono_threads_unlock ();

	do {
		mono_threads_lock ();
		if (shutting_down) {

			mono_threads_unlock ();
			break;
		}
		THREAD_DEBUG (g_message ("%s: There are %d threads to join", __func__, mono_g_hash_table_size (threads));
			mono_g_hash_table_foreach (threads, print_tids, NULL));

		ResetEvent (background_change_event);
		wait->num=0;

		memset (wait->threads, 0, MAXIMUM_WAIT_OBJECTS * SIZEOF_VOID_P);
		mono_g_hash_table_foreach (threads, build_wait_tids, wait);
		mono_threads_unlock ();
		if(wait->num>0) {

			wait_for_tids_or_state_change (wait, INFINITE);
		}
		THREAD_DEBUG (g_message ("%s: I have %d threads after waiting.", __func__, wait->num));
	} while(wait->num>0);

	mono_threads_set_shutting_down ();


	mono_runtime_set_shutting_down ();

	THREAD_DEBUG (g_message ("%s: threadpool cleanup", __func__));
	mono_thread_pool_cleanup ();


	do {
		mono_threads_lock ();

		wait->num = 0;

		memset (wait->threads, 0, MAXIMUM_WAIT_OBJECTS * SIZEOF_VOID_P);
		mono_g_hash_table_foreach_remove (threads, remove_and_abort_threads, wait);

		mono_threads_unlock ();

		THREAD_DEBUG (g_message ("%s: wait->num is now %d", __func__, wait->num));
		if(wait->num>0) {

			wait_for_tids (wait, INFINITE);
		}
	} while (wait->num > 0);


#ifndef HOST_WIN32
	sched_yield ();
#endif
}
