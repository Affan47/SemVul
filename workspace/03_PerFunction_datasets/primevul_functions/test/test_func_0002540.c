PQconnectStart(const char *conninfo)
{
	PGconn	   *conn;


	conn = makeEmptyPGconn();
	if (conn == NULL)
		return NULL;


	if (!connectOptions1(conn, conninfo))
		return conn;


	if (!connectOptions2(conn))
		return conn;


	if (!connectDBStart(conn))
	{

		conn->status = CONNECTION_BAD;
	}

	return conn;
}
