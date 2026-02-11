Cns_srv_setrltime(magic, req_data, clienthost, thip)
int magic;
char *req_data;
const char *clienthost;
struct Cns_srv_thread_info *thip;
{
	struct Cns_file_metadata filentry;
	char func[18];
	gid_t gid;
	gid_t *gids;
	char groups[256];
	char logbuf[CA_MAXSFNLEN+22];
	time_t ltime;
	int nbgids;
	char *p;
	char *rbp;
	Cns_dbrec_addr rec_addr;
	struct Cns_file_replica rep_entry;
	char sfn[CA_MAXSFNLEN+1];
	uid_t uid;
	char *user;

	strcpy (func, "Cns_srv_setrltime");
	rbp = req_data;
	unmarshall_LONG (rbp, uid);
	unmarshall_LONG (rbp, gid);
	get_client_actual_id (thip, &uid, &gid, &nbgids, &gids, &user);
	p = Cencode_groups (nbgids, gids, groups, sizeof(groups));
	nslogit (func, NS092, "setrltime", user, uid, groups, clienthost);
	if (! p) {
		sendrep (thip->s, MSG_ERR, "Too many FQANs in proxy\n");
		RETURN (EINVAL);
	}
	if (rdonly)
		RETURN (EROFS);
	if (unmarshall_STRINGN (rbp, sfn, CA_MAXSFNLEN+1))
		RETURN (SENAMETOOLONG);
	unmarshall_TIME_T (rbp, ltime);
	sprintf (logbuf, "setrltime %s %d", sfn, ltime);
	Cns_logreq (func, logbuf);


	(void) Cns_start_tr (thip->s, &thip->dbfd);

	if (Cns_get_rep_by_sfn (&thip->dbfd, sfn, &rep_entry, 1, &rec_addr))
		RETURN (serrno);


	if (Cns_get_fmd_by_fileid (&thip->dbfd, rep_entry.fileid,
	    &filentry, 0, NULL))
		RETURN (serrno);


	if (Cns_chkbackperm (&thip->dbfd, filentry.parent_fileid,
	    S_IEXEC, uid, nbgids, gids, clienthost))
		RETURN (serrno);


	if (uid != filentry.uid &&
	    Cns_chkentryperm (&filentry, S_IREAD, uid, nbgids, gids, clienthost))
		RETURN (EACCES);


	rep_entry.ltime = ltime;

	if (Cns_update_rep_entry (&thip->dbfd, &rec_addr, &rep_entry))
		RETURN (serrno);
	RETURN (0);
}
