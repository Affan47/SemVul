mkfstore(char *dir)
{
    char tbuf[1024];
    int fd;
    struct loghdr lh;
    struct idxhdr ih;

    if(access(dir, F_OK)) {
	if(mkdir(dir, 0700)) {
	    flog(LOG_ERR, "could not create %s: %s", dir, strerror(errno));
	    return(-1);
	}
    }

    snprintf(tbuf, sizeof(tbuf), "%s/log", dir);
    if((fd = open(tbuf, O_WRONLY | O_CREAT | O_EXCL, 0600)) < 0) {
	flog(LOG_ERR, "could not create log %s: %s", tbuf, strerror(errno));
	return(-1);
    }
    memcpy(lh.magic, LOGMAGIC, sizeof(LOGMAGIC));
    if(writeall(fd, &lh, sizeof(lh), 0)) {
	flog(LOG_ERR, "could not write log header: %s", strerror(errno));
	close(fd);
	return(-1);
    }
    close(fd);

    snprintf(tbuf, sizeof(tbuf), "%s/index", dir);
    if((fd = open(tbuf, O_WRONLY | O_CREAT | O_EXCL, 0600)) < 0) {
	flog(LOG_ERR, "could not create index %s: %s", tbuf, strerror(errno));
	return(-1);
    }
    memcpy(ih.magic, IDXMAGIC, sizeof(IDXMAGIC));
    ih.size = 0;
    if(writeall(fd, &ih, sizeof(ih), 0)) {
	flog(LOG_ERR, "could not write index header: %s", strerror(errno));
	close(fd);
	return(-1);
    }
    close(fd);
    return(0);
}
