lmLogFileSystem(struct jfs_log * log, struct jfs_sb_info *sbi,
			   int activate)
{
	int rc = 0;
	int i;
	struct logsuper *logsuper;
	struct lbuf *bpsuper;
	char *uuid = sbi->uuid;


	if ((rc = lbmRead(log, 1, &bpsuper)))
		return rc;

	logsuper = (struct logsuper *) bpsuper->l_ldata;
	if (activate) {
		for (i = 0; i < MAX_ACTIVE; i++)
			if (!memcmp(logsuper->active[i].uuid, NULL_UUID, 16)) {
				memcpy(logsuper->active[i].uuid, uuid, 16);
				sbi->aggregate = i;
				break;
			}
		if (i == MAX_ACTIVE) {
			jfs_warn("Too many file systems sharing journal!");
			lbmFree(bpsuper);
			return -EMFILE;
		}
	} else {
		for (i = 0; i < MAX_ACTIVE; i++)
			if (!memcmp(logsuper->active[i].uuid, uuid, 16)) {
				memcpy(logsuper->active[i].uuid, NULL_UUID, 16);
				break;
			}
		if (i == MAX_ACTIVE) {
			jfs_warn("Somebody stomped on the journal!");
			lbmFree(bpsuper);
			return -EIO;
		}

	}


	lbmDirectWrite(log, bpsuper, lbmWRITE | lbmRELEASE | lbmSYNC);
	rc = lbmIOWait(bpsuper, lbmFREE);

	return rc;
}
