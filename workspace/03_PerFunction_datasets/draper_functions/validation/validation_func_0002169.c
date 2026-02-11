io_initial_client_connect(srun_info_t *srun, slurmd_job_t *job,
			  int stdout_tasks, int stderr_tasks)
{
	int sock = -1;
	struct client_io_info *client;
	eio_obj_t *obj;

	debug4 ("adding IO connection (logical node rank %d)", job->nodeid);

	if (srun->ioaddr.sin_addr.s_addr) {
		char         ip[256];
		uint16_t     port;
		slurm_get_ip_str(&srun->ioaddr, &port, ip, sizeof(ip));
		if (ntohs(port) == 0) {
			debug3("No IO connection requested");
			return SLURM_SUCCESS;
		}
		debug4("connecting IO back to %s:%d", ip, ntohs(port));
	}

	if ((sock = (int) slurm_open_stream(&srun->ioaddr)) < 0) {
		error("connect io: %m");


		return SLURM_ERROR;
	}

	fd_set_blocking(sock);

	_send_io_init_msg(sock, srun->key, job);

	debug5("  back from _send_io_init_msg");
	fd_set_nonblocking(sock);
	fd_set_close_on_exec(sock);


	client = xmalloc(sizeof(struct client_io_info));
#ifndef NDEBUG
	client->magic = CLIENT_IO_MAGIC;
#endif
	client->job = job;
	client->msg_queue = list_create(NULL);

	client->ltaskid_stdout = stdout_tasks;
	client->ltaskid_stderr = stderr_tasks;
	client->labelio = false;
	client->label_width = 0;
	client->is_local_file = false;

	obj = eio_obj_create(sock, &client_ops, (void *)client);
	list_append(job->clients, (void *)obj);
	eio_new_initial_obj(job->eio, (void *)obj);
	debug5("Now handling %d IO Client object(s)", list_count(job->clients));

	return SLURM_SUCCESS;
}
