do_punch_hole(unsigned offset, unsigned length)
{
	unsigned end_offset;
	int max_offset = 0;
	int max_len = 0;
	int ret;

	if (length == 0) {
		if (!quiet && testcalls > simulatedopcount)
			prt("skipping zero length punch hole\n");
			log4(OP_SKIPPED, OP_PUNCH_HOLE, offset, length);
		return;
	}

	if (file_size <= (loff_t)offset) {
		if (!quiet && testcalls > simulatedopcount)
			prt("skipping hole punch off the end of the file\n");
			log4(OP_SKIPPED, OP_PUNCH_HOLE, offset, length);
		return;
	}

	end_offset = offset + length;

	log4(OP_PUNCH_HOLE, offset, length, 0);

	if (testcalls <= simulatedopcount)
		return;

	if ((progressinterval && testcalls % progressinterval == 0) ||
	    (debug && (monitorstart == -1 || monitorend == -1 ||
		      end_offset <= monitorend))) {
		prt("%lu punch\tfrom 0x%x to 0x%x, (0x%x bytes)\n", testcalls,
			offset, offset+length, length);
	}
	if ((ret = rbd_discard(image, (unsigned long long) offset,
			       (unsigned long long) length)) < 0) {
		prt("%punch hole: %x to %x\n", offset, length);
		prterrcode("do_punch_hole: discard", ret);
		report_failure(161);
	}


	max_offset = offset < file_size ? offset : file_size;
	max_len = max_offset + length <= file_size ? length :
			file_size - max_offset;
	memset(good_buf + max_offset, '\0', max_len);
}
