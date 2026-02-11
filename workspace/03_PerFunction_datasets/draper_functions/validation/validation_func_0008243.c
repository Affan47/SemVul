SQLFreeHandle(SQLSMALLINT HandleType, SQLHANDLE Handle)
{
	tdsdump_log(TDS_DBG_INFO1, "SQLFreeHandle(%d, %p)\n", HandleType, (void *) Handle);

	switch (HandleType) {
	case SQL_HANDLE_STMT:
		return _SQLFreeStmt(Handle, SQL_DROP, 0);
		break;
	case SQL_HANDLE_DBC:
		return _SQLFreeConnect(Handle);
		break;
	case SQL_HANDLE_ENV:
		return _SQLFreeEnv(Handle);
		break;
	case SQL_HANDLE_DESC:
		return _SQLFreeDesc(Handle);
		break;
	}
	return SQL_ERROR;
}
