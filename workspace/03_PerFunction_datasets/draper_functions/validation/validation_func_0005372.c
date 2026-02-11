api_jobfinish(const int sock, const jobno_t jobno)
{
	int			ret;
	struct	pend_job	*pj;
	struct	api_msg		outmsg;

	outmsg.code = API_DATAEND;
	outmsg.un.jobdata.jobno = htonl(jobno);

	if  (!(pj = find_j_by_jno(jobno)))
		outmsg.retcode = htons(XT_UNKNOWN_JOB);
	else  if  ((ret = scan_job(pj)) != XTNQ_OK  &&  ret != XTNR_WARN_LIMIT)  {
		abort_job(pj);
		outmsg.retcode = htons((SHORT)XT_CONVERT_XTNR(ret));
	}
	else  {
		outmsg.retcode = htons(ret);
		sp_req.spr_un.j.spr_act = SJ_ENQ;
		sp_req.spr_un.j.spr_pid = getpid();
		pj->jobout.spq_job = jobno;
		pj->jobout.spq_time = time((time_t *) 0);
		pj->jobout.spq_orighost = pj->clientfrom == myhostid || pj->clientfrom == localhostid? 0: pj->clientfrom;
		while  (wjmsg(&sp_req, &pj->jobout) != 0  &&  errno == EAGAIN)
			sleep(SLEEPTIME);
		fclose(pj->out_f);
		pj->out_f = (FILE *) 0;
		if  (pj->delim)  {
			free(pj->delim);
			pj->delim = (char *) 0;
		}
	}
	pushout(sock, (char *) &outmsg, sizeof(outmsg));
	if  (tracing & TRACE_APIOPEND)
		trace_op_res(Realuid, "dataend", "OK");
}
