check_blocks(void)
{
    int try, got;
    int i;
    static char blkbuf[BLOCK_SIZE * TEST_BUFFER_BLOCKS];

    if (verbose) {
	printf("Searching for bad blocks ");
	fflush(stdout);
    }
    currently_testing = 0;
    if (verbose) {
	signal(SIGALRM, alarm_intr);
	alarm(5);
    }
    try = TEST_BUFFER_BLOCKS;
    while (currently_testing < blocks) {
	if (currently_testing + try > blocks)
	    try = blocks - currently_testing;
	got = do_check(blkbuf, try, currently_testing);
	currently_testing += got;
	if (got == try) {
	    try = TEST_BUFFER_BLOCKS;
	    continue;
	} else
	    try = 1;
	if (currently_testing < start_data_block)
	    die("bad blocks before data-area: cannot make fs");

	for (i = 0; i < SECTORS_PER_BLOCK; i++)
	    mark_sector_bad(currently_testing * SECTORS_PER_BLOCK + i);
	badblocks++;
	currently_testing++;
    }

    if (verbose)
	printf("\n");

    if (badblocks)
	printf("%d bad block%s\n", badblocks, (badblocks > 1) ? "s" : "");
}
