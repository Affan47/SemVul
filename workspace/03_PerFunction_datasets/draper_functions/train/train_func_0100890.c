bt_ctf_stream_set_fd(struct bt_ctf_stream *stream, int fd)
{
	int ret = 0;

	if (stream->pos.fd != -1) {
		ret = -1;
		goto end;
	}

	ctf_init_pos(&stream->pos, NULL, fd, O_RDWR);
	stream->pos.fd = fd;
end:
	return ret;
}
