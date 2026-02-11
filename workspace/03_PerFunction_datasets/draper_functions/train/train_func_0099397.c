uplink_close(connection_t *cptr)
{
	channel_t *c;
	mowgli_patricia_iteration_state_t state;

	event_add_once("reconn", reconn, NULL, me.recontime);

	me.connected = false;

	if (curr_uplink->flags & UPF_ILLEGAL)
	{
		slog(LG_INFO, "uplink_close(): %s was removed from configuration, deleting", curr_uplink->name);
		uplink_delete(curr_uplink);
		if (uplinks.head == NULL)
		{
			slog(LG_ERROR, "uplink_close(): last uplink deleted, exiting.");
			exit(EXIT_FAILURE);
		}
		curr_uplink = uplinks.head->data;
	}
	curr_uplink->conn = NULL;

	slog(LG_DEBUG, "uplink_close(): ----------------------- clearing -----------------------");


	if (me.actual != NULL)
		server_delete(me.actual);
	me.actual = NULL;

	MOWGLI_PATRICIA_FOREACH(c, &state, chanlist)
	{
		channel_delete(c);
	}


	slog(LG_DEBUG, "uplink_close(): ------------------------- done -------------------------");
}
