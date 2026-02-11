mvapich_state_create(const mpi_plugin_client_info_t *job)
{
	mvapich_state_t *state;

	state = (mvapich_state_t *)xmalloc(sizeof(mvapich_state_t));

	state->tid		= (pthread_t)-1;
	state->mvarray          = NULL;
	state->fd               = -1;
	state->nprocs           = job->step_layout->task_cnt;
	state->protocol_version = -1;
	state->protocol_phase   = 0;
	state->connect_once     = 1;
	state->do_timing        = 0;
	state->timeout          = 600;
	state->shutdown_timeout = 5;

	if (pipe(state->shutdown_pipe) < 0) {
		error ("mvapich_state_create: pipe: %m");
		xfree(state);
		return (NULL);
	}
	fd_set_nonblocking(state->shutdown_pipe[0]);
	fd_set_nonblocking(state->shutdown_pipe[1]);
	state->shutdown_complete = false;

	slurm_mutex_init(&state->shutdown_lock);
	pthread_cond_init(&state->shutdown_cond, NULL);

	*(state->job) = *job;

	return state;
}
