compress_worker_thread_func(void *arg)
{
	comp_thread_ctxt_t *thd = (comp_thread_ctxt_t *) arg;

	pthread_mutex_lock(&thd->data_mutex);

	while (1) {
		while (!thd->data_avail && !thd->cancelled) {
			pthread_cond_wait(&thd->data_cond, &thd->data_mutex);
		}

		if (thd->cancelled)
			break;

		thd->to_len = qlz_compress(thd->from, thd->to, thd->from_len,
					   &thd->state);


		thd->adler = adler32(0x00000001, (uchar *) thd->to,
				     (uInt)thd->to_len);
	}

	pthread_mutex_unlock(&thd->data_mutex);

	return NULL;
}
