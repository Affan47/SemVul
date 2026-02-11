stat_check_fifo(struct test_fifo_struct *f)
{
    struct stat s1, s2;
    int retval = 0;

    if ((fstat(f->rdwr_fd, &s1) < 0) || (fstat(f->client_fd, &s2) < 0)) {
        perror("fstat");
	retval = -1;
	goto out;
    } else if (statcmp(&s1, &s2, ST_DEV | ST_INO | ST_NLINK)) {
	fprintf(stderr, "Post-restart fifos are not linked\n");
	retval = -1;
	goto out;
    }

    retval = statcmp(&s1, &(f->stat), ST_SIZE | ST_MODE );
    if (retval) {
	CRUT_FAIL("File attributes changed.  %d mismatches", retval);
        CRUT_DEBUG("--- Old stats ---");
        dump_stat(&(f->stat));
        CRUT_DEBUG("--- Current stats ---");
        dump_stat(&s1);
	retval = -1;
    }

out:
    return retval;
}
