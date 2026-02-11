destroy_stream(struct snd_efw *efw, struct amdtp_stream *stream)
{
	struct cmp_connection *conn;

	if (stream == &efw->tx_stream)
		conn = &efw->out_conn;
	else
		conn = &efw->in_conn;

	amdtp_stream_destroy(stream);
	cmp_connection_destroy(&efw->out_conn);
}
