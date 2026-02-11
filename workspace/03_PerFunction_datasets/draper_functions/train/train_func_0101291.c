_parse_cmd(client_req_t *req)
{
	int i = 0, len = 0;

	len = strlen (MCMD_KEY"=");
	if (! strncmp(req->buf, MCMD_KEY"=", len)) {
			req->cmd = MCMD_KEY;
			req->sep = '\n';
			req->term = '\n';
			return SLURM_SUCCESS;
	}

	len = strlen (CMD_KEY"=");
	if (strncmp(req->buf, CMD_KEY"=", len)) {
		error("mpi/pmi2: request not begin with '" CMD_KEY "='");
		error("mpi/pmi2: full request is: %s", req->buf);
		return SLURM_ERROR;
	}
	req->cmd = &req->buf[len];

	i = len;
	if (is_pmi11()) {
		req->sep = ' ';
		req->term = '\n';
		while (req->buf[i] != req->sep &&
		       req->buf[i] != req->term &&
		       i < req->buf_len) {
			i ++;
		}
	} else if (is_pmi20()) {
		req->sep = ';';
		req->term = ';';
		while (req->buf[i] != req->sep &&
		       req->buf[i] != req->term &&
		       i < req->buf_len) {
			i ++;
		}
	}
	if (i >= req->buf_len) {
		error ("mpi/pmi2: cmd not properly terminated in client request");
		return SLURM_ERROR;
	}
	req->buf[i] = '\0';

	req->parse_idx = i + 1;


	return SLURM_SUCCESS;
}
