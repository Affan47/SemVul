exec_stmt_forc(PLpgSQL_execstate *estate, PLpgSQL_stmt_forc *stmt)
{
	PLpgSQL_var *curvar;
	char	   *curname = NULL;
	PLpgSQL_expr *query;
	Portal		portal;
	int			rc;
	Datum	   *values;
	char	   *nulls;


	curvar = (PLpgSQL_var *) (estate->datums[stmt->curvar]);
	if (!curvar->isnull)
	{
		curname = TextDatumGetCString(curvar->value);
		if (SPI_cursor_find(curname) != NULL)
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_CURSOR),
					 errmsg("cursor \"%s\" already in use", curname)));
	}


	if (stmt->argquery != NULL)
	{


		PLpgSQL_stmt_execsql set_args;

		if (curvar->cursor_explicit_argrow < 0)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("arguments given for cursor without arguments")));

		memset(&set_args, 0, sizeof(set_args));
		set_args.cmd_type = PLPGSQL_STMT_EXECSQL;
		set_args.lineno = stmt->lineno;
		set_args.sqlstmt = stmt->argquery;
		set_args.into = true;

		set_args.row = (PLpgSQL_row *)
			(estate->datums[curvar->cursor_explicit_argrow]);

		if (exec_stmt_execsql(estate, &set_args) != PLPGSQL_RC_OK)
			elog(ERROR, "open cursor failed during argument processing");
	}
	else
	{
		if (curvar->cursor_explicit_argrow >= 0)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("arguments required for cursor")));
	}

	query = curvar->cursor_explicit_expr;
	Assert(query);

	if (query->plan == NULL)
		exec_prepare_plan(estate, query, curvar->cursor_options);


	eval_expr_params(estate, query, &values, &nulls);


	portal = SPI_cursor_open(curname, query->plan, values, nulls,
							 estate->readonly_func);
	if (portal == NULL)
		elog(ERROR, "could not open cursor: %s",
			 SPI_result_code_string(SPI_result));


	if (curname == NULL)
		assign_text_var(curvar, portal->name);


	rc = exec_for_query(estate, (PLpgSQL_stmt_forq *) stmt, portal, false);


	SPI_cursor_close(portal);

	if (curname == NULL)
	{
		free_var(curvar);
		curvar->value = (Datum) 0;
		curvar->isnull = true;
	}

	pfree(values);
	pfree(nulls);
	if (curname)
		pfree(curname);

	return rc;
}
