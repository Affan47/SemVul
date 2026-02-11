sendreq(int conn, char *req) {
	char buf[512];
	sprintf(buf, "%s<isr><rid>%d</rid>%s</isr>", xmlheader(),
		++requestno, req);
	if (verbose>1) {
		printf("sending %s\n", buf);
	}
	write(conn, buf, strlen(buf));
}
