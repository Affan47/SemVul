posixbg(trp)
syntaxtree *trp;
{
	char *s;
	int i, n;

	s = ((trp -> comm) -> argc > 1) ? (trp -> comm) -> argv[1] : NULL;
	checkjob(NULL);
	if ((n = getjob(s)) < 0) {
		execerror((trp -> comm) -> argv,
			(trp -> comm) -> argv[1],
			(n < -1) ? ER_TERMINATED : ER_NOSUCHJOB, 2);
		return(RET_FAIL);
	}
	if (statjob(n) > 0) Xkillpg(joblist[n].pids[0], SIGCONT);
	for (i = 0; i <= joblist[n].npipe; i++) {
		if (joblist[n].stats[i] < 0 || joblist[n].stats[i] >= 128)
			continue;
		joblist[n].stats[i] = 0;
	}
	if (!isopbg(joblist[n].trp) || !isopnown(joblist[n].trp))
		joblist[n].trp -> type = OP_BG;
	if (interactive && !nottyout) dispjob(n, Xstderr);
	prevjob = lastjob;
	lastjob = n;

	return(RET_SUCCESS);
}
