static gboolean handle_remove(MonoInternalThread *thread)
{
	gboolean ret;
	gsize tid = thread->tid;

	THREAD_DEBUG (g_message ("%s: thread ID %"G_GSIZE_FORMAT, __func__, tid));

	mono_threads_lock ();

	if (threads) {


		if (mono_g_hash_table_lookup (threads, (gpointer)tid) == thread) {
			mono_g_hash_table_remove (threads, (gpointer)tid);
			ret = TRUE;
		} else {
			ret = FALSE;
		}
	}
	else
		ret = FALSE;

	mono_threads_unlock ();


	return ret;
}
