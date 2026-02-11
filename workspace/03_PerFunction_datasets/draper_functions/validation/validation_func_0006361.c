odbc_swap_datetime_sql_type(SQLSMALLINT sql_type)
{
	switch (sql_type) {
	case SQL_TYPE_TIMESTAMP:
		sql_type = SQL_TIMESTAMP;
		break;
	case SQL_TIMESTAMP:
		sql_type = SQL_TYPE_TIMESTAMP;
		break;
	case SQL_TYPE_DATE:
		sql_type = SQL_DATE;
		break;
	case SQL_DATE:
		sql_type = SQL_TYPE_DATE;
		break;
	case SQL_TYPE_TIME:
		sql_type = SQL_TIME;
		break;
	case SQL_TIME:
		sql_type = SQL_TYPE_TIME;
		break;
	}
	return sql_type;
}
