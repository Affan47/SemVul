readbpb(devp, drv)
devstat *devp;
int drv;
{
	bpb_t bpb;
	CONST char *cp;
	int i, n;

	cp = NULL;
	devp -> fd = -1;
	for (i = 0; i < maxfdtype; i++) {
		if (drv != (int)fdtype[i].drive) continue;
		if (!cp || strcmp(cp, fdtype[i].name)) {
			bpb.nfat = 0;
			if ((devp -> fd) >= 0) VOID_C close(devp -> fd);
			memset((char *)devp, 0, sizeof(*devp));
			devp -> fd = -1;
		}
		memcpy((char *)devp, (char *)&(fdtype[i]), sizeof(*fdtype));
		cp = fdtype[i].name;
		if ((n = _readbpb(devp, &bpb)) < 0) return(-1);
		if (n > 0) break;
	}
	if (i >= maxfdtype) {
		if ((devp -> fd) >= 0) VOID_C close(devp -> fd);
		doserrno = ENODEV;
		return(-1);
	}

	return(0);
}
