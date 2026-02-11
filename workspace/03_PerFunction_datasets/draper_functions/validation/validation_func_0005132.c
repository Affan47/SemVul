mono_thread_detach (MonoThread *thread)
{
	g_return_if_fail (thread != NULL);

	THREAD_DEBUG (g_message ("%s: mono_thread_detach for %p (%"G_GSIZE_FORMAT")", __func__, thread, (gsize)thread->internal_thread->tid));

	thread_cleanup (thread->internal_thread);

	SET_CURRENT_OBJECT (NULL);
	mono_domain_unset ();


}
