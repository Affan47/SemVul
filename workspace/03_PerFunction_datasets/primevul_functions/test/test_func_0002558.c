internal_ping(PGconn *conn)
{

	if (!conn || !conn->options_valid)
		return PQPING_NO_ATTEMPT;


	if (conn->status != CONNECTION_BAD)
		(void) connectDBComplete(conn);


	if (conn->status != CONNECTION_BAD)
		return PQPING_OK;


	if (conn->auth_req_received)
		return PQPING_OK;


	if (strlen(conn->last_sqlstate) != 5)
		return PQPING_NO_RESPONSE;


	if (strcmp(conn->last_sqlstate, ERRCODE_CANNOT_CONNECT_NOW) == 0)
		return PQPING_REJECT;


	return PQPING_OK;
}
