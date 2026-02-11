rc_read(rc_t *rc)
{
	int buffer_size = safe_read(rc->fd, RC_BUFFER, RC_BUFFER_SIZE);


	if (buffer_size <= 0)
		bb_error_msg_and_die("unexpected EOF");
	rc->buffer_end = RC_BUFFER + buffer_size;
	rc->ptr = RC_BUFFER;
}
