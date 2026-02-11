print_quota(struct gfs2_inode *diq)
{
	struct gfs2_quota qbuf, q;
	int i, error;

	print_gfs2("quota file contents:");
	eol(0);
	print_gfs2("quota entries found: %d.", diq->i_di.di_size / sizeof(q));
	eol(0);
	for (i=0; ; i++) {
		error = gfs2_readi(diq, (void *)&qbuf, i * sizeof(q), sizeof(qbuf));
		if (!error)
			break;
		if (error != sizeof(qbuf)) {
			print_gfs2("Error reading quota file.");
			eol(0);
			return -1;
		}
		gfs2_quota_in(&q, (char *)&qbuf);
		print_gfs2("Entry #%d", i + 1);
		eol(0);
		gfs2_quota_print(&q);
	}
	return 0;
}
