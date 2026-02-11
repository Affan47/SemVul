listConversions(const char *pattern)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT n.nspname AS \"%s\",\n"
					  "       c.conname AS \"%s\",\n"
	   "       pg_catalog.pg_encoding_to_char(c.conforencoding) AS \"%s\",\n"
		"       pg_catalog.pg_encoding_to_char(c.contoencoding) AS \"%s\",\n"
					  "       CASE WHEN c.condefault THEN '%s'\n"
					  "       ELSE '%s' END AS \"%s\"\n"
			   "FROM pg_catalog.pg_conversion c, pg_catalog.pg_namespace n\n"
					  "WHERE n.oid = c.connamespace\n",
					  _("Schema"),
					  _("Name"),
					  _("Source"),
					  _("Destination"),
					  _("yes"),
					  _("no"),
					  _("Default?"));

	processSQLNamePattern(pset.db, &buf, pattern, true, false,
						  "n.nspname", "c.conname", NULL,
						  "pg_catalog.pg_conversion_is_visible(c.oid)");

	appendPQExpBuffer(&buf, "ORDER BY 1, 2;");

	res = PSQLexec(buf.data, false);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of conversions");

	printQuery(res, &myopt, pset.queryFout, pset.logfile);

	PQclear(res);
	return true;
}
