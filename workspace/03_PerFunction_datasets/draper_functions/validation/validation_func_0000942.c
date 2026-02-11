hisv6_fetchline(struct hisv6 *h, const HASH *hash, char *buf, off_t *poff)
{
    off_t offset;
    bool r;

    if (h != hisv6_dbzowner) {
	hisv6_seterror(h, concat("dbz not open for this history file ",
				  h->histpath, NULL));
	return false;
    }
    if ((h->flags & (HIS_RDWR | HIS_INCORE)) == (HIS_RDWR | HIS_INCORE)) {


	if (fflush(h->writefp) == EOF) {
	    hisv6_seterror(h, concat("error on history ",
				      h->histpath, " ",
				      strerror(errno), NULL));
	    r = false;
	    goto fail;
	}
    }


    errno = 0;
    r = dbzfetch(*hash, &offset);
#ifdef ESTALE


    if (!r && errno == ESTALE) {
	hisv6_closefiles(h);
	if (!hisv6_reopen(h)) {
	    hisv6_closefiles(h);
	    r = false;
	    goto fail;
	}
    }
#endif
    if (r) {
	ssize_t n;

	do {
	    n = pread(h->readfd, buf, HISV6_MAXLINE, offset);
#ifdef ESTALE
	    if (n == -1 && errno == ESTALE) {
		hisv6_closefiles(h);
		if (!hisv6_reopen(h)) {
		    hisv6_closefiles(h);
		    r = false;
		    goto fail;
		}
	    }
#endif
	} while (n == -1 && errno == EINTR);
	if (n >= HISV6_MINLINE) {
	    char *p;

	    buf[n] = '\0';
	    p = strchr(buf, '\n');
	    if (!p) {
		char location[HISV6_MAX_LOCATION];

		hisv6_errloc(location, (size_t)-1, offset);
		hisv6_seterror(h,
				concat("can't locate end of line in history ",
				       h->histpath, location,
				       NULL));
		r = false;
	    } else {
		*p = '\0';
		*poff = offset;
		r = true;
	    }
	} else {
	    char location[HISV6_MAX_LOCATION];

	    hisv6_errloc(location, (size_t)-1, offset);
	    hisv6_seterror(h, concat("line too short in history ",
				      h->histpath, location,
				      NULL));
	    r = false;

	}
    } else {

	r = false;
    }
 fail:
    return r;
}
