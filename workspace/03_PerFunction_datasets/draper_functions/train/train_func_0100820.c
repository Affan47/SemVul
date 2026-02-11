transient_server_callback(IPC_Channel *client, gpointer user_data)
{
	int lpc = 0;
	IPC_Message *msg = NULL;
	char *buffer = NULL;
	IPC_Message *reply = NULL;
	int llpc = 0;

    cl_log(LOG_DEBUG, "channel: %p", client);

    cl_log(LOG_DEBUG, "Client status %d (disconnect=%d)", client->ch_status, IPC_DISCONNECT);

    while(client->ops->is_message_pending(client)) {
    		if (client->ch_status == IPC_DISCONNECT) {


			break;
	        }
		if(client->ops->recv(client, &msg) != IPC_OK) {
			cl_perror("[Server] Receive failure");
			return FALSE;
		}

		if (msg != NULL) {
			lpc++;
			buffer = (char*)g_malloc(msg->msg_len+1);
			memcpy(buffer,msg->msg_body, msg->msg_len);
			buffer[msg->msg_len] = '\0';
			cl_log(LOG_DEBUG, "[Server] Got xml [text=%s]", buffer);

			reply = create_simple_message(strdup(buffer), client);
			if (!reply) {
				cl_log(LOG_ERR, "[Server] Could allocate reply msg.");
				return FALSE;
			}

			llpc = 0;
			while(llpc++ < MAX_IPC_FAIL && client->ops->send(client, reply) == IPC_FAIL) {
				cl_log(LOG_WARNING, "[Server] ipc channel blocked");
				cl_shortsleep();
			}

			if(lpc == MAX_IPC_FAIL) {
				cl_log(LOG_ERR, "[Server] Could not send IPC, message.  Channel is dead.");
				free(reply);
				return FALSE;
			}

			cl_log(LOG_DEBUG, "[Server] Sent reply");
			msg->msg_done(msg);
		} else {
			cl_log(LOG_ERR, "[Server] No message this time");
			continue;
		}
	}

	cl_log(LOG_DEBUG, "[Server] Processed %d messages", lpc);

	cl_log(LOG_DEBUG, "[Server] Client status %d", client->ch_status);
	if(client->ch_status != IPC_CONNECT) {
		cl_log(LOG_INFO, "[Server] Server received HUP from child");
		return FALSE;
	}

	return TRUE;
}
