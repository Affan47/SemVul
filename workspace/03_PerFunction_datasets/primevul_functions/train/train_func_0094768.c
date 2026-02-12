static void wait_a_bit(void *ctx)
{
	struct timeval when;
	REQUEST *request = ctx;
	fr_event_callback_t callback = NULL;

	rad_assert(request->magic == REQUEST_MAGIC);

#ifdef WITH_COA


	if (request->coa && !request->coa->proxy_reply &&
	    request->coa->next_callback) {
		request->coa->when = request->coa->next_when;
		INSERT_EVENT(request->coa->next_callback, request->coa);
		request->coa->next_callback = NULL;
		request->coa->parent = NULL;
		request->coa = NULL;
	}
#endif

	switch (request->child_state) {
	case REQUEST_QUEUED:
	case REQUEST_RUNNING:


#ifdef HAVE_PTHREAD_H
		if (!have_children)
#endif
		{
			rad_assert("We do not have threads, but the request is marked as queued or running in a child thread" == NULL);
			break;
		}

#ifdef HAVE_PTHREAD_H


		when = request->received;
		when.tv_sec += request->root->max_request_time;


		fr_event_now(el, &now);


		if (timercmp(&now, &when, <)) {
			if (request->delay < (USEC / 10)) {
				request->delay = USEC / 10;
			}
			request->delay += request->delay >> 1;


			if (request->delay > (request->root->max_request_time * USEC)) {
				request->delay = request->root->max_request_time * USEC;
			}

			request->when = now;
			tv_add(&request->when, request->delay);
			callback = wait_a_bit;
			break;
		}

		request->master_state = REQUEST_STOP_PROCESSING;


		if (have_children &&
		    (pthread_equal(request->child_pid, NO_SUCH_CHILD_PID) == 0)) {
			radlog(L_ERR, "WARNING: Unresponsive child for request %u, in module %s component %s",
			       request->number,
			       request->module ? request->module : "<server core>",
			       request->component ? request->component : "<server core>");
		}

		request->delay = USEC;
		tv_add(&request->when, request->delay);
		callback = wait_for_child_to_die;
		break;
#endif


	case REQUEST_DONE:
#ifdef HAVE_PTHREAD_H
		request->child_pid = NO_SUCH_CHILD_PID;
#endif

#ifdef WITH_COA


		if (!request->in_request_hash &&
		    request->proxy &&
		    (request->packet->code != request->proxy->code) &&
		    ((request->proxy->code == PW_COA_REQUEST) ||
		     (request->proxy->code == PW_DISCONNECT_REQUEST))) {


			ev_request_free(&request);
			return;
		}
#endif
		request_stats_final(request);
		cleanup_delay(request);
		return;

	case REQUEST_REJECT_DELAY:
	case REQUEST_CLEANUP_DELAY:
#ifdef HAVE_PTHREAD_H
		request->child_pid = NO_SUCH_CHILD_PID;
#endif
		request_stats_final(request);

	case REQUEST_PROXIED:
		rad_assert(request->next_callback != NULL);
		rad_assert(request->next_callback != wait_a_bit);

		request->when = request->next_when;
		callback = request->next_callback;
		request->next_callback = NULL;
		break;

	default:
		rad_panic("Internal sanity check failure");
		return;
	}


	if (!callback) {
		RDEBUG("WARNING: Internal sanity check failed in event handler for request %u: Discarding the request!", request->number);
		ev_request_free(&request);
		return;
	}

	INSERT_EVENT(callback, request);
}
