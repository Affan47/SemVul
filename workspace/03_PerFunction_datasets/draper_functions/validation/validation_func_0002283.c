xmms_ipc_register_broadcast (xmms_ipc_client_t *client,
                             xmms_ipc_msg_t *msg, xmmsv_t *arguments)
{
	xmmsv_t *arg;
	gint32 broadcastid;
	int r;

	if (!arguments || !xmmsv_list_get (arguments, 0, &arg)) {
		xmms_log_error ("No broadcastid in this msg?!");
		return;
	}

	r = xmmsv_get_int (arg, &broadcastid);

	if (!r) {
		xmms_log_error ("Cannot extract broadcast id from value");
		return;
	}

	if (broadcastid < 0 || broadcastid >= XMMS_IPC_SIGNAL_END) {
		xmms_log_error ("Bad broadcast id (%d)", broadcastid);
		return;
	}

	g_mutex_lock (client->lock);
	client->broadcasts[broadcastid] =
		g_list_append (client->broadcasts[broadcastid],
				GUINT_TO_POINTER (xmms_ipc_msg_get_cookie (msg)));

	g_mutex_unlock (client->lock);
}
