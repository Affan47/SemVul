cancellable_locks_cancelled_cb (GCancellable *cancellable,
                                struct _ECancellableLocksBase *base)
{
	g_return_if_fail (base != NULL);


	g_mutex_lock (&base->cond_mutex);
	g_cond_broadcast (&base->cond);
	g_mutex_unlock (&base->cond_mutex);
}
