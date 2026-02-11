stepd_attach(int fd, slurm_addr_t *ioaddr, slurm_addr_t *respaddr,
	     void *job_cred_sig, reattach_tasks_response_msg_t *resp)
{
	int req = REQUEST_ATTACH;
	int rc = SLURM_SUCCESS;

	safe_write(fd, &req, sizeof(int));
	safe_write(fd, ioaddr, sizeof(slurm_addr_t));
	safe_write(fd, respaddr, sizeof(slurm_addr_t));
	safe_write(fd, job_cred_sig, SLURM_IO_KEY_SIZE);


	safe_read(fd, &rc, sizeof(int));

	if (rc == SLURM_SUCCESS) {

		uint32_t ntasks;
		int len, i;

		safe_read(fd, &ntasks, sizeof(uint32_t));
		resp->ntasks = ntasks;
		len = ntasks * sizeof(uint32_t);

		resp->local_pids = xmalloc(len);
		safe_read(fd, resp->local_pids, len);

		resp->gtids = xmalloc(len);
		safe_read(fd, resp->gtids, len);

		resp->executable_names =
			(char **)xmalloc(sizeof(char *) * ntasks);
		for (i = 0; i < ntasks; i++) {
			safe_read(fd, &len, sizeof(int));
			resp->executable_names[i] = (char *)xmalloc(len);
			safe_read(fd, resp->executable_names[i], len);
		}
	}

	return rc;
rwfail:
	return SLURM_ERROR;
}
