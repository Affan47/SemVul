pcap_fopen_offline(FILE *fp, char *errbuf)
{
	register pcap_t *p;
	bpf_u_int32 magic;
	size_t amt_read;
	u_int i;

	p = pcap_create_common("(savefile)", errbuf);
	if (p == NULL)
		return (NULL);


	amt_read = fread((char *)&magic, 1, sizeof(magic), fp);
	if (amt_read != sizeof(magic)) {
		if (ferror(fp)) {
			snprintf(errbuf, PCAP_ERRBUF_SIZE,
			    "error reading dump file: %s",
			    pcap_strerror(errno));
		} else {
			snprintf(errbuf, PCAP_ERRBUF_SIZE,
			    "truncated dump file; tried to read %lu file header bytes, only got %lu",
			    (unsigned long)sizeof(magic),
			    (unsigned long)amt_read);
		}
		goto bad;
	}


	for (i = 0; i < N_FILE_TYPES; i++) {
		switch ((*check_headers[i])(p, magic, fp, errbuf)) {

		case -1:


			goto bad;

		case 1:


			goto found;
		}
	}


	snprintf(errbuf, PCAP_ERRBUF_SIZE, "unknown file format");
	goto bad;

found:
	p->sf.rfile = fp;

#ifdef PCAP_FDDIPAD

	p->fddipad = 0;
#endif

#if !defined(WIN32) && !defined(MSDOS)


	p->selectable_fd = fileno(fp);
#endif

	p->read_op = pcap_offline_read;
	p->inject_op = sf_inject;
	p->setfilter_op = install_bpf_program;
	p->setdirection_op = sf_setdirection;
	p->set_datalink_op = NULL;
	p->getnonblock_op = sf_getnonblock;
	p->setnonblock_op = sf_setnonblock;
	p->stats_op = sf_stats;
#ifdef WIN32
	p->setbuff_op = sf_setbuff;
	p->setmode_op = sf_setmode;
	p->setmintocopy_op = sf_setmintocopy;
#endif
	p->cleanup_op = sf_cleanup;
	p->activated = 1;

	return (p);
 bad:
	free(p);
	return (NULL);
}
