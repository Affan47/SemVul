dumpdata(void *addr, int len, FILE *f)
{
	int tocopy;
	struct romfh *ri;

	if (!len)
		return;
	if (atoffs >= 512) {
		fwrite(addr, len, 1, f);
		atoffs+=len;
		return;
	}

	tocopy = len < 512-atoffs ? len : 512-atoffs;
	memcpy(fixbuf+atoffs, addr, tocopy);
	atoffs+=tocopy;
	addr=(char*)addr+tocopy;
	len-=tocopy;

	if (atoffs==512) {
		ri = (struct romfh *)&fixbuf;
		fixsum(ri, atoffs<ntohl(ri->size)?atoffs:ntohl(ri->size));
		if (fwrite(fixbuf, atoffs, 1, f) != 1) {
			perror(outf);
			exit(1);
		}
	}
	if (len) {
		if (fwrite(addr, len, 1, f) != 1) {
			perror(outf);
			exit(1);
		}
		atoffs+=len;
	}
}
