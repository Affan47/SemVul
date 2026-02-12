connectOptions1(PGconn *conn, const char *conninfo)
{
	PQconninfoOption *connOptions;


	connOptions = parse_connection_string(conninfo, &conn->errorMessage, true);
	if (connOptions == NULL)
	{
		conn->status = CONNECTION_BAD;

		return false;
	}


	if (!fillPGconn(conn, connOptions))
	{
		conn->status = CONNECTION_BAD;
		PQconninfoFree(connOptions);
		return false;
	}


	PQconninfoFree(connOptions);

	return true;
}
