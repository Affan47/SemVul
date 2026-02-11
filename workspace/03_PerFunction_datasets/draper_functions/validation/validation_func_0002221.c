iscsi_tcp_set_max_r2t(struct iscsi_conn *conn, char *buf)
{
	struct iscsi_session *session = conn->session;
	unsigned short r2ts = 0;

	sscanf(buf, "%hu", &r2ts);
	if (session->max_r2t == r2ts)
		return 0;

	if (!r2ts || !is_power_of_2(r2ts))
		return -EINVAL;

	session->max_r2t = r2ts;
	iscsi_tcp_r2tpool_free(session);
	return iscsi_tcp_r2tpool_alloc(session);
}
