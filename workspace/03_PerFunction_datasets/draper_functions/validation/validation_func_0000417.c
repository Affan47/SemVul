Linux_ReadCDTOC(int cd_fd) {
	cdrom_tochdr toc_header;
	cdrom_tocentry toc_entry;
	CD_TDesc* a_TOC_desc = NULL;
	CD_TDesc* prev_desc = NULL;

	if (ioctl(cd_fd, CDROMREADTOCHDR, &toc_header) == -1) {
		fprintf(stderr, "AtomicParsley error: there was an error reading the CD Table of Contents header.\n");
		return;
	}
	cdTOC = (CD_TOC_*)calloc(1, sizeof(CD_TOC_));


	cdTOC->track_description = NULL;

	for (uint8_t i = toc_header.cdth_trk0; i <= toc_header.cdth_trk1+1; i++) {
		memset(&toc_entry, 0, sizeof(toc_entry));
		if (i == toc_header.cdth_trk1+1) {
			toc_entry.cdte_track = CDROM_LEADOUT;
		} else {
			toc_entry.cdte_track = i;
		}
		toc_entry.cdte_format = CDROM_MSF;

		if (ioctl(cd_fd, CDROMREADTOCENTRY, &toc_entry) == -1) {
      fprintf(stderr, "AtomicParsley error: there was an error reading a CD Table of Contents entry (linux cdrom).\n");
			return;
    }

		if (cdTOC->track_description == NULL) {
			cdTOC->track_description = (CD_TDesc*)calloc(1, (sizeof(CD_TDesc)));
			a_TOC_desc = cdTOC->track_description;
			prev_desc = a_TOC_desc;
		} else {
			prev_desc->next_description = (CD_TDesc*)calloc(1, (sizeof(CD_TDesc)));
			a_TOC_desc = (CD_TDesc*)prev_desc->next_description;
			prev_desc = a_TOC_desc;
		}

		a_TOC_desc->session = 1;
#if defined (__ppc__) || defined (__ppc64__)
		a_TOC_desc->controladdress = (toc_entry.cdte_ctrl << 4) | toc_entry.cdte_adr;
#else
		a_TOC_desc->controladdress = (toc_entry.cdte_adr << 4) | toc_entry.cdte_ctrl;
#endif
		a_TOC_desc->unused1 = 0;
		a_TOC_desc->tracknumber = toc_entry.cdte_track;
		a_TOC_desc->rel_minutes = 0;
		a_TOC_desc->rel_seconds = 0;
		a_TOC_desc->rel_frames = 0;
		a_TOC_desc->zero_space = 0;
		a_TOC_desc->abs_minutes = toc_entry.cdte_addr.msf.minute;
		a_TOC_desc->abs_seconds = toc_entry.cdte_addr.msf.second;
		a_TOC_desc->abs_frames = toc_entry.cdte_addr.msf.frame;
	}
	return;
}
