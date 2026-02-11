exec_stmts(PLpgSQL_execstate *estate, List *stmts)
{
	ListCell   *s;

	if (stmts == NIL)
	{


		CHECK_FOR_INTERRUPTS();
		return PLPGSQL_RC_OK;
	}

	foreach(s, stmts)
	{
		PLpgSQL_stmt *stmt = (PLpgSQL_stmt *) lfirst(s);
		int			rc = exec_stmt(estate, stmt);

		if (rc != PLPGSQL_RC_OK)
			return rc;
	}

	return PLPGSQL_RC_OK;
}
