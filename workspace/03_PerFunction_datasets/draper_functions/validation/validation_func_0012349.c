check_memory_stats(int conn, int warn, int crit, char *param) {
	int rc=0;
	struct xmltree *response;
	int total=0, temp;
	char buf[80], parmbuf[80], *p, *r;

	sendreq(conn, "<m>-1</m>");
	response=xmlparsefd(conn);

	strcpy(parmbuf, param);
	p=strtok(parmbuf, ",");
	while (p) {
		strcpy(buf, "isr/MEM/");
		strcat(buf, p);
		if ((r=xmlvalue(response, buf))==NULL) {
			addcheckresult(3, 'm', p, 0, warn, crit, 0, -1);
			return;
		}
		temp=atoi(r);
		total+=temp;
		p=strtok(NULL, ",");
	}

	if	(crit>0 && total>crit) { rc=2; }
	else if	(crit<0 && total<-crit) { rc=2; }
	else if	(warn>0 && total>warn) { rc=1; }
	else if	(warn<0 && total<-warn) { rc=1; }
	addcheckresult(rc, 'm', param, total, warn, crit, 0, 100);
	xmlfreetree(response);
}
