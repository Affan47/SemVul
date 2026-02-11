conn_free(struct conn_info *ci)
{
	int free_it;

	pthread_mutex_lock(&ci->mutex);
	if (--ci->use_count == 0)
		free_it = 1;
	else
		free_it = 0;
	pthread_mutex_unlock(&ci->mutex);
	if (free_it)
		free(ci);
}
