slurm_free_launch_tasks_request_msg(launch_tasks_request_msg_t * msg)
{
	int i;

	if (msg == NULL)
		return;

	slurm_cred_destroy(msg->cred);

	if (msg->env) {
		for (i = 0; i < msg->envc; i++) {
			xfree(msg->env[i]);
		}
		xfree(msg->env);
	}
	xfree(msg->alias_list);
	xfree(msg->cwd);
	xfree(msg->cpu_bind);
	xfree(msg->mem_bind);
	if (msg->argv) {
		for (i = 0; i < msg->argc; i++) {
			xfree(msg->argv[i]);
		}
		xfree(msg->argv);
	}
	for (i = 0; i < msg->spank_job_env_size; i++) {
		xfree(msg->spank_job_env[i]);
	}
	xfree(msg->spank_job_env);
	if(msg->nnodes && msg->global_task_ids)
		for(i=0; i<msg->nnodes; i++) {
			xfree(msg->global_task_ids[i]);
		}
	xfree(msg->tasks_to_launch);
	xfree(msg->cpus_allocated);
	xfree(msg->resp_port);
	xfree(msg->io_port);
	xfree(msg->global_task_ids);
	xfree(msg->ifname);
	xfree(msg->ofname);
	xfree(msg->efname);

	xfree(msg->task_prolog);
	xfree(msg->task_epilog);
	xfree(msg->complete_nodelist);

	xfree(msg->ckpt_dir);
	xfree(msg->restart_dir);

	if (msg->switch_job)
		switch_free_jobinfo(msg->switch_job);

	if (msg->options)
		job_options_destroy(msg->options);

	if (msg->select_jobinfo)
		select_g_select_jobinfo_free(msg->select_jobinfo);

	xfree(msg);
}
