connectDBStart(PGconn *conn)
{
	if (!conn)
		return 0;

	if (!conn->options_valid)
		goto connect_errReturn;


	if (!pg_link_canary_is_frontend())
	{
		appendPQExpBufferStr(&conn->errorMessage,
							 "libpq is incorrectly linked to backend functions\n");
		goto connect_errReturn;
	}


	conn->inStart = conn->inCursor = conn->inEnd = 0;
	conn->outCount = 0;


	conn->whichhost = -1;
	conn->try_next_addr = false;
	conn->try_next_host = true;
	conn->status = CONNECTION_NEEDED;


	if (conn->target_server_type == SERVER_TYPE_PREFER_STANDBY_PASS2)
		conn->target_server_type = SERVER_TYPE_PREFER_STANDBY;


	if (PQconnectPoll(conn) == PGRES_POLLING_WRITING)
		return 1;

connect_errReturn:


	pqDropConnection(conn, true);
	conn->status = CONNECTION_BAD;
	return 0;
}
