lkcd_dumpfile_complaint(uint32_t realpages, uint32_t dh_num_pages, int retval)
{
	if (lkcd->flags & LKCD_BAD_DUMP)
		return;

	lkcd->flags |= LKCD_BAD_DUMP;

	if (realpages > dh_num_pages) {
		lkcd_print(
"\n\nWARNING: This dumpfile contains more pages than the amount indicated\n"
"         in the dumpfile header.  This is indicative of a failure during\n"
"         the post-panic creation of the dumpfile on the dump device.\n\n");
	}

	if (realpages < dh_num_pages) {
		lkcd_print(
"\n\nWARNING: This dumpfile contains fewer pages than the amount indicated\n"
"         in the dumpfile header.  This is indicative of a failure during\n"
"         the creation of the dumpfile during boot.\n\n");
	}
}
