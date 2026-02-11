printstatus(FILE* const file1, FILE* const file2,
		 const int bs, const int sync)
{
	float t1, t2;
	clock_t cl;
	static int einvalwarn = 0;

	if (file1 == stderr || file1 == stdout)
		fprintf(file1, "%s%s%s%s", up, up, up, up);
	if (file2 == stderr || file2 == stdout)
		fprintf(file2, "%s%s%s%s", up, up, up, up);

	if (sync) {
		int err = fsync(odes);
		if (err && (errno != EINVAL || !einvalwarn) &&!o_chr) {
			fplog(stderr, "dd_rescue: (warning): sync %s (%.1fk): %s!  \n",
			      oname, (float)ipos/1024, strerror(errno));
			++einvalwarn;
		}
		errno = 0;
	}

	gettimeofday(&currenttime, NULL);
	t1 = difftimetv(&currenttime, &starttime);
	t2 = difftimetv(&currenttime, &lasttime);
	cl = clock();

	if (file1)
		doprint(file1, bs, cl, t1, t2, sync);
	if (file2)
		doprint(file2, bs, cl, t1, t2, sync);
	if (1 || sync) {
		memcpy(&lasttime, &currenttime, sizeof(lasttime));
		lxfer = xfer;
	}
}
