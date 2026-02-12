void check_file_actlst(int *ifd, char *dfile, struct activity *act[], uint64_t flags,
		       struct file_magic *file_magic, struct file_header *file_hdr,
		       struct file_activity **file_actlst, unsigned int id_seq[],
		       int ignore, int *endian_mismatch, int *arch_64)
{
	int i, j, k, p;
	struct file_activity *fal;
	void *buffer = NULL;
	size_t bh_size = FILE_HEADER_SIZE;
	size_t ba_size = FILE_ACTIVITY_SIZE;


	if (sa_open_read_magic(ifd, dfile, file_magic, ignore, endian_mismatch, TRUE) < 0)


		return;


	if ((file_magic->header_size <= MIN_FILE_HEADER_SIZE) ||
	    (file_magic->header_size > MAX_FILE_HEADER_SIZE)) {
#ifdef DEBUG
		fprintf(stderr, "%s: header_size=%u\n",
			__FUNCTION__, file_magic->header_size);
#endif
		goto format_error;
	}


	if (file_magic->header_size > FILE_HEADER_SIZE) {
		bh_size = file_magic->header_size;
	}
	SREALLOC(buffer, char, bh_size);


	sa_fread(*ifd, buffer, (size_t) file_magic->header_size, HARD_SIZE, UEOF_STOP);


	if (remap_struct(hdr_types_nr, file_magic->hdr_types_nr, buffer,
			 file_magic->header_size, FILE_HEADER_SIZE, bh_size) < 0)
		goto format_error;

	memcpy(file_hdr, buffer, FILE_HEADER_SIZE);
	free(buffer);
	buffer = NULL;


	*arch_64 = (file_hdr->sa_sizeof_long == SIZEOF_LONG_64BIT);


	if (*endian_mismatch) {
		swap_struct(hdr_types_nr, file_hdr, *arch_64);
	}


	if ((file_hdr->sa_act_nr > MAX_NR_ACT) ||
	    (file_hdr->act_size > MAX_FILE_ACTIVITY_SIZE) ||
	    (file_hdr->rec_size > MAX_RECORD_HEADER_SIZE) ||
	    (MAP_SIZE(file_hdr->act_types_nr) > file_hdr->act_size) ||
	    (MAP_SIZE(file_hdr->rec_types_nr) > file_hdr->rec_size)) {
#ifdef DEBUG
		fprintf(stderr, "%s: sa_act_nr=%d act_size=%u rec_size=%u map_size(act)=%u map_size(rec)=%u\n",
			__FUNCTION__, file_hdr->sa_act_nr, file_hdr->act_size, file_hdr->rec_size,
			MAP_SIZE(file_hdr->act_types_nr), MAP_SIZE(file_hdr->rec_types_nr));
#endif

		goto format_error;
	}


	if (file_hdr->act_size > FILE_ACTIVITY_SIZE) {
		ba_size = file_hdr->act_size;
	}
	SREALLOC(buffer, char, ba_size);
	SREALLOC(*file_actlst, struct file_activity, FILE_ACTIVITY_SIZE * file_hdr->sa_act_nr);
	fal = *file_actlst;


	j = 0;
	for (i = 0; i < file_hdr->sa_act_nr; i++, fal++) {


		sa_fread(*ifd, buffer, (size_t) file_hdr->act_size, HARD_SIZE, UEOF_STOP);


		if (remap_struct(act_types_nr, file_hdr->act_types_nr, buffer,
			     file_hdr->act_size, FILE_ACTIVITY_SIZE, ba_size) < 0)
			goto format_error;
		memcpy(fal, buffer, FILE_ACTIVITY_SIZE);


		if (*endian_mismatch) {
			swap_struct(act_types_nr, fal, *arch_64);
		}


		if ((fal->nr < 1) || (fal->nr2 < 1) ||
		    (fal->nr > NR_MAX) || (fal->nr2 > NR2_MAX) ||
		    (fal->size <= 0)) {
#ifdef DEBUG
			fprintf(stderr, "%s: id=%d nr=%d nr2=%d\n",
				__FUNCTION__, fal->id, fal->nr, fal->nr2);
#endif
			goto format_error;
		}

		if ((p = get_activity_position(act, fal->id, RESUME_IF_NOT_FOUND)) < 0)

			continue;

		if (act[p]->magic != fal->magic) {

			if (ignore) {


				act[p]->magic = ACTIVITY_MAGIC_UNKNOWN;
			}
			else
				continue;
		}


		if (fal->nr > act[p]->nr_max) {
#ifdef DEBUG
			fprintf(stderr, "%s: id=%d nr=%d nr_max=%d\n",
				__FUNCTION__, fal->id, fal->nr, act[p]->nr_max);
#endif
			goto format_error;
		}


		if (!(((fal->types_nr[0] >= act[p]->gtypes_nr[0]) &&
		     (fal->types_nr[1] >= act[p]->gtypes_nr[1]) &&
		     (fal->types_nr[2] >= act[p]->gtypes_nr[2]))
		     ||
		     ((fal->types_nr[0] <= act[p]->gtypes_nr[0]) &&
		     (fal->types_nr[1] <= act[p]->gtypes_nr[1]) &&
		     (fal->types_nr[2] <= act[p]->gtypes_nr[2]))) && !ignore) {
#ifdef DEBUG
			fprintf(stderr, "%s: id=%d file=%d,%d,%d activity=%d,%d,%d\n",
				__FUNCTION__, fal->id, fal->types_nr[0], fal->types_nr[1], fal->types_nr[2],
				act[p]->gtypes_nr[0], act[p]->gtypes_nr[1], act[p]->gtypes_nr[2]);
#endif
			goto format_error;
		}

		if (MAP_SIZE(fal->types_nr) > fal->size) {
#ifdef DEBUG
		fprintf(stderr, "%s: id=%d size=%u map_size=%u\n",
			__FUNCTION__, fal->id, fal->size, MAP_SIZE(fal->types_nr));
#endif
			goto format_error;
		}

		for (k = 0; k < 3; k++) {
			act[p]->ftypes_nr[k] = fal->types_nr[k];
		}

		if (fal->size > act[p]->msize) {
			act[p]->msize = fal->size;
		}

		act[p]->nr_ini = fal->nr;
		act[p]->nr2    = fal->nr2;
		act[p]->fsize  = fal->size;


		id_seq[j++] = fal->id;
	}

	while (j < NR_ACT) {
		id_seq[j++] = 0;
	}

	free(buffer);
	buffer = NULL;


	for (i = 0; i < NR_ACT; i++) {

		if (!IS_SELECTED(act[i]->options))
			continue;


		fal = *file_actlst;
		for (j = 0; j < file_hdr->sa_act_nr; j++, fal++) {
			if (act[i]->id == fal->id)
				break;
		}
		if (j == file_hdr->sa_act_nr) {

			act[i]->options &= ~AO_SELECTED;
		}
	}


	if (!get_activity_nr(act, AO_SELECTED, COUNT_ACTIVITIES) && !DISPLAY_HDR_ONLY(flags)) {
		fprintf(stderr, _("Requested activities not available in file %s\n"),
			dfile);
		close(*ifd);
		exit(1);
	}


	if (file_hdr->extra_next && (skip_extra_struct(*ifd, *endian_mismatch, *arch_64) < 0))
		goto format_error;

	return;

format_error:
	if (buffer) {
		free(buffer);
	}
	handle_invalid_sa_file(*ifd, file_magic, dfile, 0);
}
