findLog(FILE *fp, int *in_use)
{
	struct logsuper logsup;
	struct superblock sb;

	*in_use = 0;


	if (rdwrSuper(fp, &sb, PB_READ)) {
		fsck_send_msg(lrdo_NOTAFSDEV);
		return NOT_FSDEV_ERROR;
	}


	if (memcmp(sb.s_magic, JFS_MAGIC, sizeof (sb.s_magic)) == 0) {


		if ((sb.s_flag & JFS_INLINELOG) == JFS_INLINELOG) {
			Log.location = INLINELOG;
			Log.fp = fp;

			Log.l2bsize = sb.s_l2bsize;
			Log.xaddr = addressPXD(&sb.s_logpxd) << sb.s_l2bsize;


			vopen[0].status = sb.s_state;
			vopen[0].fp = fp;

			return 0;
		}

		primary_vol.fp = fp;
		uuid_copy(primary_vol.uuid, sb.s_uuid);


		Log.xaddr = 0;
		if (log_device[0]) {
			Log.fp = NULL;
			if (LogOpenMode != O_RDONLY) {
				Log.fp = fopen_excl(log_device, "r+");
				if (Log.fp == NULL)
					*in_use = 1;
			}
			if (Log.fp == NULL) {
				Log.fp = fopen(log_device, "r");
				if (Log.fp == NULL) {
					printf("Invalid journal specified (%s)\n",
					       log_device);
					goto by_uuid;
				}
			}
			ujfs_rw_diskblocks(Log.fp, LOGPNTOB(LOGSUPER_B),
					   sizeof (struct logsuper), &logsup, GET);
			ujfs_swap_logsuper(&logsup);
			if ((logsup.magic != LOGMAGIC) || (uuid_compare(logsup.uuid, sb.s_loguuid))) {
				fclose(Log.fp);
				*in_use = 0;
				goto by_uuid;
			}
			Log.location = OUTLINELOG;
			return 0;
		}
	      by_uuid:
		Log.fp = open_by_label(sb.s_loguuid, 0, 1, NULL, in_use);

		if (Log.fp != NULL) {
			Log.location |= OUTLINELOG;
			return 0;
		}

		return NOT_INLINELOG_ERROR;
	}


	ujfs_rw_diskblocks(fp, LOGPNTOB(LOGSUPER_B), sizeof (struct logsuper), &logsup, GET);
	ujfs_swap_logsuper(&logsup);
	if (logsup.magic != LOGMAGIC) {
		fsck_send_msg(lrdo_NOTAFSDEV);
		return NOT_FSDEV_ERROR;
	}
	Log.fp = fp;
	Log.location = OUTLINELOG;

	return 0;
}
