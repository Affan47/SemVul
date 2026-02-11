e_cancellable_rec_mutex_init (ECancellableRecMutex *rec_mutex)
{
	g_return_if_fail (rec_mutex != NULL);

	g_rec_mutex_init (&rec_mutex->rec_mutex);
	g_mutex_init (&rec_mutex->base.cond_mutex);
	g_cond_init (&rec_mutex->base.cond);
}
