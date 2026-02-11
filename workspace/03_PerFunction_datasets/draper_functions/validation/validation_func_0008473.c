run_health_check(void)
{
#ifdef HAVE_FRONT_END
	front_end_record_t *front_end_ptr;
#else
	struct node_record *node_ptr;
	int node_states = slurmctld_conf.health_check_node_state;
#endif
	int i;
	char *host_str = NULL;
	agent_arg_t *check_agent_args = NULL;

	check_agent_args = xmalloc (sizeof (agent_arg_t));
	check_agent_args->msg_type = REQUEST_HEALTH_CHECK;
	check_agent_args->retry = 0;
	check_agent_args->hostlist = hostlist_create("");
#ifdef HAVE_FRONT_END
	for (i = 0, front_end_ptr = front_end_nodes;
	     i < front_end_node_cnt; i++, front_end_ptr++) {
		if (IS_NODE_NO_RESPOND(front_end_ptr))
			continue;
		hostlist_push(check_agent_args->hostlist, front_end_ptr->name);
		check_agent_args->node_count++;
	}
#else
	if ((node_states != HEALTH_CHECK_NODE_ANY) &&
	    (node_states != HEALTH_CHECK_NODE_IDLE)) {

		select_g_select_nodeinfo_set_all();
	}

	for (i=0, node_ptr=node_record_table_ptr;
	     i<node_record_count; i++, node_ptr++) {
		if (IS_NODE_NO_RESPOND(node_ptr) || IS_NODE_FUTURE(node_ptr) ||
		    IS_NODE_POWER_SAVE(node_ptr))
			continue;
		if (node_states != HEALTH_CHECK_NODE_ANY) {
			uint16_t cpus_total, cpus_used = 0;
			if (slurmctld_conf.fast_schedule) {
				cpus_total = node_ptr->config_ptr->cpus;
			} else {
				cpus_total = node_ptr->cpus;
			}
			if (!IS_NODE_IDLE(node_ptr)) {
				select_g_select_nodeinfo_get(
						node_ptr->select_nodeinfo,
						SELECT_NODEDATA_SUBCNT,
						NODE_STATE_ALLOCATED,
						&cpus_used);
			}
			if (cpus_used == 0) {
				if (!(node_states & HEALTH_CHECK_NODE_IDLE))
					continue;
			} else if (cpus_used < cpus_total) {
				if (!(node_states & HEALTH_CHECK_NODE_MIXED))
					continue;
			} else {
				if (!(node_states & HEALTH_CHECK_NODE_ALLOC))
					continue;
			}
		}

		hostlist_push(check_agent_args->hostlist, node_ptr->name);
		check_agent_args->node_count++;
	}
#endif

	if (check_agent_args->node_count == 0) {
		hostlist_destroy(check_agent_args->hostlist);
		xfree (check_agent_args);
	} else {
		hostlist_uniq(check_agent_args->hostlist);
		host_str = hostlist_ranged_string_xmalloc(
				check_agent_args->hostlist);
		debug("Spawning health check agent for %s", host_str);
		xfree(host_str);
		ping_begin();
		agent_queue_request(check_agent_args);
	}
}
