_handle_name_lookup(int fd, Buf buf)
{
	int rc;
	uint32_t tmp32;
	char *name = NULL, *port = NULL;
	Buf resp_buf = NULL;

	debug3("mpi/pmi2: in _handle_name_lookup");

	safe_unpackstr_xmalloc(&name, &tmp32, buf);

	if (tree_info.srun_addr)
		port = name_lookup_up(name);
	else
		port = name_lookup_local(name);
out:
	resp_buf = init_buf(1024);
	packstr(port, resp_buf);
	rc = _slurm_msg_sendto(fd, get_buf_data(resp_buf),
			       get_buf_offset(resp_buf),
			       SLURM_PROTOCOL_NO_SEND_RECV_FLAGS);
	free_buf(resp_buf);
	xfree(name);
	xfree(port);

	debug3("mpi/pmi2: out _handle_name_lookup");
	return rc;

unpack_error:
	rc = SLURM_ERROR;
	goto out;
}
