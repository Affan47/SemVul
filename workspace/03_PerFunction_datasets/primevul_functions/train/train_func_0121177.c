void read_header_data(void)
{
	struct file_magic file_magic;
	struct file_activity file_act;
	int rc, i, p;
	char version[16];


	rc = sa_read(&file_magic, FILE_MAGIC_SIZE);

	sprintf(version, "%d.%d.%d.%d",
		file_magic.sysstat_version,
		file_magic.sysstat_patchlevel,
		file_magic.sysstat_sublevel,
		file_magic.sysstat_extraversion);
	if (!file_magic.sysstat_extraversion) {
		version[strlen(version) - 2] = '\0';
	}

	if (rc || (file_magic.sysstat_magic != SYSSTAT_MAGIC) ||
	    (file_magic.format_magic != FORMAT_MAGIC) ||
	    strcmp(version, VERSION)) {


		if (!rc && (file_magic.sysstat_magic == SYSSTAT_MAGIC)) {
			fprintf(stderr,
				_("Using a wrong data collector from a different sysstat version\n"));
		}

#ifdef DEBUG
		fprintf(stderr, "%s: sysstat_magic=%x format_magic=%x version=%s\n",
			__FUNCTION__, file_magic.sysstat_magic, file_magic.format_magic, version);
#endif
		print_read_error(INCONSISTENT_INPUT_DATA);
	}


	if (sa_read(&file_hdr, FILE_HEADER_SIZE)) {
#ifdef DEBUG
		fprintf(stderr, "%s: File header\n", __FUNCTION__);
#endif
		print_read_error(END_OF_DATA_UNEXPECTED);
	}


	if (file_hdr.sa_act_nr > NR_ACT) {
#ifdef DEBUG
		fprintf(stderr, "%s: sa_act_nr=%d\n", __FUNCTION__, file_hdr.sa_act_nr);
#endif
		print_read_error(INCONSISTENT_INPUT_DATA);
	}

	if ((file_hdr.act_size != FILE_ACTIVITY_SIZE) ||
	    (file_hdr.rec_size != RECORD_HEADER_SIZE)) {
#ifdef DEBUG
		fprintf(stderr, "%s: act_size=%u/%lu rec_size=%u/%lu\n", __FUNCTION__,
			file_hdr.act_size, FILE_ACTIVITY_SIZE, file_hdr.rec_size, RECORD_HEADER_SIZE);
#endif
		print_read_error(INCONSISTENT_INPUT_DATA);
	}


	for (i = 0; i < file_hdr.sa_act_nr; i++) {

		if (sa_read(&file_act, FILE_ACTIVITY_SIZE)) {
#ifdef DEBUG
			fprintf(stderr, "%s: File activity (%d)\n", __FUNCTION__, i);
#endif
			print_read_error(END_OF_DATA_UNEXPECTED);
		}

		p = get_activity_position(act, file_act.id, RESUME_IF_NOT_FOUND);

		if ((p < 0) || (act[p]->fsize != file_act.size)
			    || (act[p]->gtypes_nr[0] != file_act.types_nr[0])
			    || (act[p]->gtypes_nr[1] != file_act.types_nr[1])
			    || (act[p]->gtypes_nr[2] != file_act.types_nr[2])
			    || (file_act.nr <= 0)
			    || (file_act.nr2 <= 0)
			    || (act[p]->magic != file_act.magic)) {
#ifdef DEBUG
			if (p < 0) {
				fprintf(stderr, "%s: p=%d\n", __FUNCTION__, p);
			}
			else {
				fprintf(stderr, "%s: %s: size=%d/%d magic=%x/%x nr=%d nr2=%d types=%d,%d,%d/%d,%d,%d\n",
					__FUNCTION__, act[p]->name, act[p]->fsize, file_act.size,
					act[p]->magic, file_act.magic, file_act.nr, file_act.nr2,
					act[p]->gtypes_nr[0], act[p]->gtypes_nr[1], act[p]->gtypes_nr[2],
					file_act.types_nr[0], file_act.types_nr[1], file_act.types_nr[2]);
			}
#endif

			print_read_error(INCONSISTENT_INPUT_DATA);
		}

		id_seq[i]      = file_act.id;
		act[p]->nr_ini = file_act.nr;
		act[p]->nr2    = file_act.nr2;
	}

	while (i < NR_ACT) {
		id_seq[i++] = 0;
	}


	reverse_check_act(file_hdr.sa_act_nr);

	return;
}
