PQerrorMessage(const PGconn *conn)
{
	if (!conn)
		return libpq_gettext("connection pointer is NULL\n");


	if (PQExpBufferBroken(&conn->errorMessage))
		return libpq_gettext("out of memory\n");

	return conn->errorMessage.data;
}
