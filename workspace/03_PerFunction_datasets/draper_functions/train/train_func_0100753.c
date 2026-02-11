request_enqueue(REQUEST *request)
{


	if ((last_cleaned < request->timestamp) ||
	    (thread_pool.active_threads == thread_pool.total_threads)) {
		thread_pool_manage(request->timestamp);
	}

	pthread_mutex_lock(&thread_pool.queue_mutex);

	thread_pool.request_count++;

	if (thread_pool.num_queued >= thread_pool.max_queue_size) {
		int complain = FALSE;
		time_t now;
		static time_t last_complained = 0;

		now = time(NULL);
		if (last_complained != now) {
			last_complained = now;
			complain = TRUE;
		}

		pthread_mutex_unlock(&thread_pool.queue_mutex);


		if (complain) {
			radlog(L_ERR, "Something is blocking the server.  There are %d packets in the queue, waiting to be processed.  Ignoring the new request.", thread_pool.max_queue_size);
		}
		return 0;
	}
	request->component = "<core>";
	request->module = "<queue>";


	if (!fr_fifo_push(thread_pool.fifo[request->priority], request)) {
		pthread_mutex_unlock(&thread_pool.queue_mutex);
		radlog(L_ERR, "!!! ERROR !!! Failed inserting request %d into the queue", request->number);
		return 0;
	}

	thread_pool.num_queued++;

	pthread_mutex_unlock(&thread_pool.queue_mutex);


	sem_post(&thread_pool.semaphore);

	return 1;
}
