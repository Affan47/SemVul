listForeignDataWrappers(const char *pattern, bool verbose)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	if (pset.sversion < 80400)
	{
		fprintf(stderr, _("The server (version %d.%d) does not support foreign-data wrappers.\n"),
				pset.sversion / 10000, (pset.sversion / 100) % 100);
		return true;
	}

	initPQExpBuffer(&buf);
	printfPQExpBuffer(&buf,
					  "SELECT fdwname AS \"%s\",\n"
					  "  pg_catalog.pg_get_userbyid(fdwowner) AS \"%s\",\n",
					  gettext_noop("Name"),
					  gettext_noop("Owner"));
	if (pset.sversion >= 90100)
		appendPQExpBuffer(&buf,
						  "  fdwhandler::pg_catalog.regproc AS \"%s\",\n",
						  gettext_noop("Handler"));
	appendPQExpBuffer(&buf,
					  "  fdwvalidator::pg_catalog.regproc AS \"%s\"",
					  gettext_noop("Validator"));

	if (verbose)
	{
		appendPQExpBuffer(&buf, ",\n  ");
		printACLColumn(&buf, "fdwacl");
		appendPQExpBuffer(&buf,
						  ",\n  fdwoptions AS \"%s\"",
						  gettext_noop("Options"));
	}

	appendPQExpBuffer(&buf, "\nFROM pg_catalog.pg_foreign_data_wrapper\n");

	processSQLNamePattern(pset.db, &buf, pattern, false, false,
						  NULL, "fdwname", NULL, NULL);

	appendPQExpBuffer(&buf, "ORDER BY 1;");

	res = PSQLexec(buf.data, false);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of foreign-data wrappers");
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, pset.logfile);

	PQclear(res);
	return true;
}
