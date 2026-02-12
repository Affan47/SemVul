pgpassfileWarning(PGconn *conn)
{


	if (conn->password_needed &&
		conn->connhost[conn->whichhost].password != NULL &&
		conn->result)
	{
		const char *sqlstate = PQresultErrorField(conn->result,
												  PG_DIAG_SQLSTATE);

		if (sqlstate && strcmp(sqlstate, ERRCODE_INVALID_PASSWORD) == 0)
			appendPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("password retrieved from file \"%s\"\n"),
							  conn->pgpassfile);
	}
}
