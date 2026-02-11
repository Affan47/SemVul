dpm_get_reqs4del(dbfd, bol, time_lower, time_upper, max_recs, dpm_req, rec_addr, endlist, dblistptr)
struct dpm_dbfd *dbfd;
int bol;
time_t time_lower;
time_t time_upper;
int max_recs;
struct dpm_req *dpm_req;
dpm_dbrec_addr *rec_addr;
int endlist;
DBLISTPTR *dblistptr;
{
	char func[17];
	static char query4upd[] =
		"SELECT ROWID, \
		 R_ORDINAL, R_TOKEN, R_UID, \
		 R_GID, CLIENT_DN, CLIENTHOST, \
		 R_TYPE, U_TOKEN, \
		 FLAGS, RETRYTIME, NBREQFILES, \
		 CTIME, STIME, ETIME, \
		 STATUS, ERRSTRING, GROUPS \
		FROM dpm_req \
		WHERE ctime = %d \
		AND (status = %d OR status >= %d)";
	static char query4updlim1[] =
		"SELECT ROWID, \
		 R_ORDINAL, R_TOKEN, R_UID, \
		 R_GID, CLIENT_DN, CLIENTHOST, \
		 R_TYPE, U_TOKEN, \
		 FLAGS, RETRYTIME, NBREQFILES, \
		 CTIME, STIME, ETIME, \
		 STATUS, ERRSTRING, GROUPS \
		FROM dpm_req \
		WHERE ctime <= %d \
		AND (status = %d OR status >= %d) \
		LIMIT %d";
	static char query4updlim2[] =
		"SELECT ROWID, \
		 R_ORDINAL, R_TOKEN, R_UID, \
		 R_GID, CLIENT_DN, CLIENTHOST, \
		 R_TYPE, U_TOKEN, \
		 FLAGS, RETRYTIME, NBREQFILES, \
		 CTIME, STIME, ETIME, \
		 STATUS, ERRSTRING, GROUPS \
		FROM dpm_req \
		WHERE ctime BETWEEN %d AND %d \
		AND (status = %d OR status >= %d) \
		LIMIT %d";
	MYSQL_ROW row;
	char sql_stmt[1024];

	strcpy (func, "dpm_get_reqs4del");
	if (endlist) {
		if (*dblistptr)
			mysql_free_result (*dblistptr);
		return (1);
	}
	if (bol) {
		*dblistptr = NULL;
		if (max_recs) {
			if (time_lower != 0) {
				dm_snprintf (sql_stmt, sizeof(sql_stmt),
				    query4updlim2, time_lower, time_upper,
				    DPM_SUCCESS, DPM_DONE, max_recs);
			} else {
				dm_snprintf (sql_stmt, sizeof(sql_stmt),
				    query4updlim1, time_upper, DPM_SUCCESS,
				    DPM_DONE, max_recs);
			}
		} else {
			if (time_lower != time_upper) {
				serrno = EINVAL;
				return (-1);
			}
			dm_snprintf (sql_stmt, sizeof(sql_stmt), query4upd,
			    time_lower, DPM_SUCCESS, DPM_DONE);
		}
		if (dpm_exec_query (func, dbfd, sql_stmt, dblistptr))
			return (-1);
	}
	if ((row = mysql_fetch_row (*dblistptr)) == NULL) {
		return (1);
	}
	dpm_decode_xferreq_entry (row, 1, rec_addr, dpm_req);
	return (0);
}
