dpm_get_gfr_by_pfn(dbfd, bol, pfn, gfr_entry, lock, rec_addr, endlist, dblistptr)
struct dpm_dbfd *dbfd;
int bol;
char *pfn;
struct dpm_get_filereq *gfr_entry;
int lock;
dpm_dbrec_addr *rec_addr;
int endlist;
DBLISTPTR *dblistptr;
{
	char escaped_name[CA_MAXSFNLEN*2+1];
	char func[19];
	static char query[] =
		"SELECT \
		 R_TOKEN, F_ORDINAL, R_UID, FROM_SURL, \
		 PROTOCOL, LIFETIME, F_TYPE, S_TOKEN, \
		 RET_POLICY, FLAGS, SERVER, PFN, \
		 ACTUAL_SIZE, STATUS, ERRSTRING \
		FROM dpm_get_filereq \
		WHERE pfn = '%s'";
	static char query4upd[] =
		"SELECT ROWID, \
		 R_TOKEN, F_ORDINAL, R_UID, FROM_SURL, \
		 PROTOCOL, LIFETIME, F_TYPE, S_TOKEN, \
		 RET_POLICY, FLAGS, SERVER, PFN, \
		 ACTUAL_SIZE, STATUS, ERRSTRING \
		FROM dpm_get_filereq \
		WHERE pfn = '%s' \
		FOR UPDATE";
	PGresult *res;
	char sql_stmt[2423];

	strcpy (func, "dpm_get_gfr_by_pfn");
	if (endlist) {
		PQclear (dblistptr->res);
		return (1);
	}
	if (bol) {
		PQescapeStringConn (dbfd->Pconn, escaped_name, pfn,
		    strlen (pfn), NULL);
		sprintf (sql_stmt, lock ? query4upd : query, escaped_name);
		res = PQexec (dbfd->Pconn, sql_stmt);
		if (PQresultStatus (res) != PGRES_TUPLES_OK) {
			dpm_libpq_error (func, "SELECT", res, dbfd);
			return (-1);
		}
		dblistptr->res = res;
		dblistptr->row = 0;
	}
	if (dblistptr->row >= PQntuples (dblistptr->res))
		return (1);
	dpm_decode_gfr_entry (dblistptr->res, dblistptr->row, lock, rec_addr, gfr_entry);
	dblistptr->row++;
	return (0);
}
