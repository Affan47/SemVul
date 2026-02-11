dbregparam(DBPROCESS * dbproc, char *param_name, int type, DBINT datalen, BYTE * data)
{
	tdsdump_log(TDS_DBG_FUNC, "dbregparam(%p, %s, %d, %d, %p)\n", dbproc, param_name, type, datalen, data);
	CHECK_DBPROC();
	DBPERROR_RETURN(IS_TDSDEAD(dbproc->tds_socket), SYBEDDNE);
	CHECK_NULP(param_name, "dbregparam", 2, FAIL);
	CHECK_NULP(data, "dbregparam", 5, FAIL);
	tdsdump_log(TDS_DBG_FUNC, "UNIMPLEMENTED dbregparam()\n");
	return SUCCEED;
}
