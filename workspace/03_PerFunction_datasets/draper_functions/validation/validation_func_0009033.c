AcceptResult(const PGresult *result)
{
	bool		OK = true;

	if (!result)
		OK = false;
	else
		switch (PQresultStatus(result))
		{
			case PGRES_COMMAND_OK:
			case PGRES_TUPLES_OK:
			case PGRES_EMPTY_QUERY:
			case PGRES_COPY_IN:
			case PGRES_COPY_OUT:

				break;

			default:
				OK = false;
				break;
		}

	if (!OK)
	{
		const char *error = PQerrorMessage(pset.db);

		if (strlen(error))
			psql_error("%s", error);

		CheckConnection();
	}

	return OK;
}
