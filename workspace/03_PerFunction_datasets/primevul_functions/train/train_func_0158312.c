gboolean mono_thread_interruption_requested ()
{
	if (thread_interruption_requested) {
		MonoInternalThread *thread = mono_thread_internal_current ();

		if (thread != NULL)
			return (thread->interruption_requested);
	}
	return FALSE;
}
