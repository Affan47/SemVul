PQconnectStartParams(const char *const *keywords,
					 const char *const *values,
					 int expand_dbname)
{
	PGconn	   *conn;
	PQconninfoOption *connOptions;


	conn = makeEmptyPGconn();
	if (conn == NULL)
		return NULL;


	connOptions = conninfo_array_parse(keywords, values,
									   &conn->errorMessage,
									   true, expand_dbname);
	if (connOptions == NULL)
	{
		conn->status = CONNECTION_BAD;

		return conn;
	}


	if (!fillPGconn(conn, connOptions))
	{
		PQconninfoFree(connOptions);
		return conn;
	}


	PQconninfoFree(connOptions);


	if (!connectOptions2(conn))
		return conn;


	if (!connectDBStart(conn))
	{

		conn->status = CONNECTION_BAD;
	}

	return conn;
}
