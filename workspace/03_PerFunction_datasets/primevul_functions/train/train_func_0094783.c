static void proxy_fallback_handler(REQUEST *request)
{


	request->delay = USEC / 10;
	gettimeofday(&now, NULL);
	request->next_when = now;
	tv_add(&request->next_when, request->delay);
	request->next_callback = wait_a_bit;


	request->child_state = REQUEST_QUEUED;

	rad_assert(request->proxy != NULL);
	if (!thread_pool_addrequest(request, virtual_server_handler)) {
		request->child_state = REQUEST_DONE;
	}

#ifdef HAVE_PTHREAD_H


	if (have_children) wait_a_bit(request);
#endif
}
