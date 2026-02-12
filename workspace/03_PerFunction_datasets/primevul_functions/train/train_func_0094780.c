static void post_proxy_fail_handler(REQUEST *request)
{


	request->delay = USEC / 10;
	gettimeofday(&now, NULL);


	if (!setup_post_proxy_fail(request)) {
		request_post_handler(request);

	} else {


		request->child_state = REQUEST_QUEUED;


		request->priority = 0;
		rad_assert(request->proxy != NULL);
		thread_pool_addrequest(request, null_handler);
	}


	if (have_children) wait_a_bit(request);
}
