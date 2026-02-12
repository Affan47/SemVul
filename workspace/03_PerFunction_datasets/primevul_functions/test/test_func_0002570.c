PQhostaddr(const PGconn *conn)
{
	if (!conn)
		return NULL;


	if (conn->connhost != NULL && conn->connip != NULL)
		return conn->connip;

	return "";
}
