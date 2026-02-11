p_mpi_hook_client_fini(mpi_plugin_client_state_t *state)
{
	if (p4_tid != (pthread_t)-1) {
		char tmp = 1;
		int n;


		n = write(shutdown_pipe[1], &tmp, 1);
		if (n == 1) {
			struct timespec ts = {0, 0};

			slurm_mutex_lock(&shutdown_lock);
			ts.tv_sec = time(NULL) + shutdown_timeout;

			while (!shutdown_complete) {
				if (time(NULL) >= ts.tv_sec) {
					break;
				}
				pthread_cond_timedwait(
					&shutdown_cond,
					&shutdown_lock, &ts);
			}
			slurm_mutex_unlock(&shutdown_lock);
		}
		if (shutdown_complete) {
			close(shutdown_pipe[0]);
			close(shutdown_pipe[1]);

			slurm_mutex_destroy(&shutdown_lock);
			pthread_cond_destroy(&shutdown_cond);
		}
		p4_tid = (pthread_t) -1;
	}
	return SLURM_SUCCESS;
}
