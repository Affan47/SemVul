table_exist(DB_DATABASE *db, char *table)
{

#ifdef ODBC_DEBUG_HEADER
fprintf(stderr,"[ODBC][%s][%d]\n",__FILE__,__LINE__);
fprintf(stderr,"\ttable_exist\n");
fflush(stderr);
#endif
	SQLHSTMT statHandle;

	SQLRETURN nReturn = -1;
	SQLRETURN retcode;
	SQLCHAR szTableName[101] = "";
	SQLCHAR szTableType[101] = "";
	SQLCHAR szTableRemarks[301] = "";
	SQLLEN nIndicatorName;
	SQLLEN nIndicatorType;
	SQLLEN nIndicatorRemarks;
	int compare = -1;
	ODBC_CONN *han = (ODBC_CONN *)db->handle;
	int len;

	len = strlen(table);
	if (len == 0)
		return FALSE;

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, han->odbcHandle, &statHandle);

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
	{
		return FALSE;
	}


	if (SQL_SUCCESS != (nReturn = SQLTables(statHandle, 0, 0, 0, 0, 0, 0, 0, 0)))
	{
		return FALSE;
	}

	SQLBindCol(statHandle, SQLTables_TABLE_NAME, SQL_C_CHAR, szTableName,
						 sizeof(szTableName), &nIndicatorName);
	SQLBindCol(statHandle, SQLTables_TABLE_TYPE, SQL_C_CHAR, szTableType,
						 sizeof(szTableType), &nIndicatorType);
	SQLBindCol(statHandle, SQLTables_REMARKS, SQL_C_CHAR, szTableRemarks,
						 sizeof(szTableRemarks), &nIndicatorRemarks);

	nReturn = SQLFetch(statHandle);
	while ((nReturn == SQL_SUCCESS || nReturn == SQL_SUCCESS_WITH_INFO)
				 && compare != 0)
	{

		compare = strncmp((char *)szTableName, table, len);
		szTableName[0] = '\0';
		szTableType[0] = '\0';
		szTableRemarks[0] = '\0';
		nReturn = SQLFetch(statHandle);
	}


	nReturn = SQLFreeHandle(SQL_HANDLE_STMT, statHandle);

	if (compare == 0)
		return TRUE;
	else
		return FALSE;

}
