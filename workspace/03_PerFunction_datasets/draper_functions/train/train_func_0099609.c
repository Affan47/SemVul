dbaltop(DBPROCESS * dbproc, int computeid, int column)
{
	TDSCOLUMN *curcol;

	tdsdump_log(TDS_DBG_FUNC, "dbaltop(%p, %d, %d)\n", dbproc, computeid, column);
	CHECK_PARAMETER(dbproc, SYBENULL, -1);

	if ((curcol=dbacolptr(dbproc, computeid, column, 0)) == NULL)
		return -1;

	return curcol->column_operator;
}
