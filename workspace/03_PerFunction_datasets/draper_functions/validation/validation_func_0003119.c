check_table(PGconn *db_conn, char *schema, char *table,
	    storage_field_t *fields, char *constraint)
{
	DEF_VARS;
	char **tables = NULL;
	int i, num, rc = SLURM_SUCCESS;

	query = xstrdup_printf(
		"SELECT tablename FROM pg_tables WHERE schemaname='%s' AND "
		"tableowner='%s' AND tablename !~ '^pg_+' "
		"AND tablename !~ '^sql_+'", schema, PQuser(db_conn));
	result = pgsql_db_query_ret(db_conn, query);
	xfree(query);
	if (!result)
		return SLURM_ERROR;

	num = PQntuples(result);
	tables = xmalloc(sizeof(char *) * (num + 1));
	for (i = 0; i < num; i ++)
		tables[i] = xstrdup(PQgetvalue(result, i, 0));
	tables[num] = NULL;
	PQclear(result);

	i = 0;
	while (tables[i] && strcmp(tables[i], table))
		i ++;

	if (!tables[i]) {
		debug("as/pg: table %s.%s not found, create it", schema, table);
		rc = pgsql_db_create_table(db_conn, schema, table, fields,
					   constraint);
	} else {
		rc = pgsql_db_make_table_current(
			db_conn, schema, table, fields);
	}
	for (i = 0; i < num; i ++)
		xfree(tables[i]);
	xfree(tables);
	return rc;
}
