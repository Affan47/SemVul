Cns_unique_uid(dbfd, unique_id)
struct Cns_dbfd *dbfd;
unsigned int *unique_id;
{
	char func[15];
	static char insert_stmt[] =
		"INSERT INTO Cns_unique_uid (ID) VALUES (101)";
	static char query_stmt[] =
		"SELECT ID FROM Cns_unique_uid FOR UPDATE";
	MYSQL_RES *res;
	MYSQL_ROW row;
	char sql_stmt[1024];
	unsigned int uniqueid;
	static char update_stmt[] =
		"UPDATE Cns_unique_uid SET ID = %d";

	strcpy (func, "Cns_unique_uid");
	(void) Cthread_mutex_lock (&oneuniqueuid);
	if (Cns_exec_query (func, dbfd, query_stmt, &res)) {
		(void) Cthread_mutex_unlock (&oneuniqueuid);
		return (-1);
	}
	if ((row = mysql_fetch_row (res)) == NULL) {
		mysql_free_result (res);
		if (mysql_query (&dbfd->mysql, insert_stmt)) {
			(void) Cthread_mutex_unlock (&oneuniqueuid);
			Cns_mysql_error (func, "INSERT", dbfd);
			return (-1);
		}
		*unique_id = 101;
	} else {
		uniqueid = atoi (row[0]) + 1;
		mysql_free_result (res);
		dm_snprintf (sql_stmt, sizeof(sql_stmt), update_stmt, uniqueid);
		if (mysql_query (&dbfd->mysql, sql_stmt)) {
			(void) Cthread_mutex_unlock (&oneuniqueuid);
			Cns_mysql_error (func, "UPDATE", dbfd);
			return (-1);
		}
		*unique_id = uniqueid;
	}
	(void) Cthread_mutex_unlock (&oneuniqueuid);
	return (0);
}
