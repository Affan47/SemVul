jack_messagebuffer_exit ()
{
	if (!mb_initialized)
		return;

	pthread_mutex_lock(&mb_write_lock);
	mb_initialized = 0;
	pthread_cond_signal(&mb_ready_cond);
	pthread_mutex_unlock(&mb_write_lock);

	pthread_join(mb_writer_thread, NULL);
	mb_flush();

	if (mb_overruns)
		jack_error("WARNING: %d message buffer overruns!",
			mb_overruns);

	pthread_mutex_destroy(&mb_write_lock);
	pthread_cond_destroy(&mb_ready_cond);
}
