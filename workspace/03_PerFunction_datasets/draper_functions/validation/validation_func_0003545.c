_queue_agent_retry(agent_info_t * agent_info_ptr, int count)
{
	agent_arg_t *agent_arg_ptr;
	queued_request_t *queued_req_ptr = NULL;
	thd_t *thread_ptr = agent_info_ptr->thread_struct;
	int i, j;

	if (count == 0)
		return;


	agent_arg_ptr = xmalloc(sizeof(agent_arg_t));
	agent_arg_ptr->node_count = count;
	agent_arg_ptr->retry = 1;
	agent_arg_ptr->hostlist = hostlist_create("");
	agent_arg_ptr->msg_type = agent_info_ptr->msg_type;
	agent_arg_ptr->msg_args = *(agent_info_ptr->msg_args_pptr);
	*(agent_info_ptr->msg_args_pptr) = NULL;

	j = 0;
	for (i = 0; i < agent_info_ptr->thread_count; i++) {
		if (!thread_ptr[i].ret_list) {
			if (thread_ptr[i].state != DSH_NO_RESP)
				continue;

			debug("got the name %s to resend",
			      thread_ptr[i].nodelist);
			hostlist_push(agent_arg_ptr->hostlist,
				      thread_ptr[i].nodelist);

			if ((++j) == count)
				break;
		} else {
			if (_setup_requeue(agent_arg_ptr, &thread_ptr[i],
					  count, &j))
				break;
		}
	}
	if (count != j) {
		error("agent: Retry count (%d) != actual count (%d)",
			count, j);
		agent_arg_ptr->node_count = j;
	}
	debug2("Queue RPC msg_type=%u, nodes=%d for retry",
	       agent_arg_ptr->msg_type, j);


	queued_req_ptr = xmalloc(sizeof(queued_request_t));
	queued_req_ptr->agent_arg_ptr = agent_arg_ptr;
	queued_req_ptr->last_attempt  = time(NULL);
	slurm_mutex_lock(&retry_mutex);
	if (retry_list == NULL) {
		retry_list = list_create(_list_delete_retry);
		if (retry_list == NULL)
			fatal("list_create failed");
	}
	if (list_append(retry_list, (void *) queued_req_ptr) == 0)
		fatal("list_append failed");
	slurm_mutex_unlock(&retry_mutex);
}
