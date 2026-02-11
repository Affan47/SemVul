remove_did_entry(struct afp_volume * volume, const char * name)
{
	struct did_cache_entry * d, * p=NULL;

	pthread_mutex_lock(&volume->did_cache_mutex);

	for (d=volume->did_cache_base;d;d=d->next)
	{
		if (strcmp(d->dirname,name)==0) {
			if (p)
				p->next=d->next;
			else
				volume->did_cache_base=d->next;
			volume->did_cache_stats.force_removed++;
			free(d);
			break;
		} else
			p=d;
	}
	pthread_mutex_unlock(&volume->did_cache_mutex);
	return 0;
}
