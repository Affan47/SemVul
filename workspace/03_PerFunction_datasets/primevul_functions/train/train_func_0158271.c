static void wait_for_tids (struct wait_data *wait, guint32 timeout)
{
	guint32 i, ret;

	THREAD_DEBUG (g_message("%s: %d threads to wait for in this batch", __func__, wait->num));

	ret=WaitForMultipleObjectsEx(wait->num, wait->handles, TRUE, timeout, TRUE);

	if(ret==WAIT_FAILED) {

		THREAD_DEBUG (g_message ("%s: Wait failed", __func__));
		return;
	}

	for(i=0; i<wait->num; i++)
		CloseHandle (wait->handles[i]);

	if (ret == WAIT_TIMEOUT)
		return;

	for(i=0; i<wait->num; i++) {
		gsize tid = wait->threads[i]->tid;

		mono_threads_lock ();
		if(mono_g_hash_table_lookup (threads, (gpointer)tid)!=NULL) {


			mono_threads_unlock ();
			THREAD_DEBUG (g_message ("%s: cleaning up after thread %p (%"G_GSIZE_FORMAT")", __func__, wait->threads[i], tid));
			thread_cleanup (wait->threads[i]);
		} else {
			mono_threads_unlock ();
		}
	}
}
