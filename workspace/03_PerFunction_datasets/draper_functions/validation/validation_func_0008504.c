Cns_insert_group_entry(dbfd, group_entry)
struct Cns_dbfd *dbfd;
struct Cns_groupinfo *group_entry;
{
	char func[23];
	static char insert_stmt[] =
		"INSERT INTO Cns_groupinfo (GID, GROUPNAME, BANNED) VALUES (%d, '%s', %d)";
	PGresult *res;
	char sql_stmt[1024];

	strcpy (func, "Cns_insert_group_entry");
	sprintf (sql_stmt, insert_stmt, group_entry->gid, group_entry->groupname,
	    group_entry->banned);
	res = PQexec (dbfd->Pconn, sql_stmt);
	if (PQresultStatus (res) != PGRES_COMMAND_OK) {
		if (strstr (PQresultErrorMessage (res), "duplicate")) {
			serrno = EEXIST;
			PQclear (res);
		} else
			Cns_libpq_error (func, "INSERT", res, dbfd);
		return (-1);
	}
	PQclear (res);
	return (0);
}
