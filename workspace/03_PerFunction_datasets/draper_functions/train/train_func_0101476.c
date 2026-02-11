bin_save_pipe(FILE * f, pipe_op_t * op_it) {
	int rv;
	int32_t i32;
	char c = OP_PIPE;

	write_char(c);
	write_int32(op_it->fd1);
	write_int32(op_it->fd2);
	write_int32(op_it->mode);
	write_int32(op_it->retval);

	if ( (rv = bin_write_info(f, &op_it->info)) != 0) {
		BIN_WRITE_ERROR;
	}

	return 0;
}
