init_prng(void) {
	int db = 0, bytes, ubytes, fd;
	char file[MSZ], dtmp[100];
	unsigned int sr;

	RAND_file_name(file, MSZ);

	rfbLog("RAND_file_name: %s\n", file);

	bytes = RAND_load_file(file, -1);
	if (db) fprintf(stderr, "bytes read: %d\n", bytes);

	ubytes = RAND_load_file("/dev/urandom", 64);
	bytes += ubytes;
	if (db) fprintf(stderr, "bytes read: %d / %d\n", bytes, ubytes);


	sprintf(dtmp, "/tmp/p%.8f.XXXXXX", dnow());
	fd = mkstemp(dtmp);
	RAND_add(dtmp, strlen(dtmp), 0);
	if (fd >= 0) {
		close(fd);
		unlink(dtmp);
	}
	sprintf(dtmp, "%d-%.8f", (int) getpid(), dnow());
	RAND_add(dtmp, strlen(dtmp), 0);

	if (!RAND_status()) {
		ubytes = -1;
		rfbLog("calling RAND_poll()\n");
		RAND_poll();
	}

	RAND_bytes((unsigned char *)&sr, 4);
	srand(sr);

	if (bytes > 0) {
		if (! quiet) {
			rfbLog("initialized PRNG with %d random bytes.\n",
			    bytes);
		}
		if (ubytes > 32 && rnow() < 0.25) {
			RAND_write_file(file);
		}
		return;
	}

	bytes += RAND_load_file("/dev/random", 8);
	if (db) fprintf(stderr, "bytes read: %d\n", bytes);
	RAND_poll();

	if (! quiet) {
		rfbLog("initialized PRNG with %d random bytes.\n", bytes);
	}
}
