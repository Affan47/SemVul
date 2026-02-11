socket_del_ipcmsg(IPC_Message* m)
{
	if (m == NULL) {
		cl_log(LOG_ERR, "socket_del_ipcmsg:"
		       "msg is NULL");
		return;
	}

	if (m->msg_body) {
		memset(m->msg_body, 0, m->msg_len);
	}
	if (m->msg_buf) {
		g_free(m->msg_buf);
	}

	memset(m, 0, sizeof(*m));
	g_free(m);

	ipcmsg_count_freed ++;
}
