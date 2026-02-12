static int fsmMkfile(int dirfd, rpmfi fi, struct filedata_s *fp, rpmfiles files,
		     rpmpsm psm, int nodigest,
		     struct filedata_s ** firstlink, int *firstlinkfile,
		     int *fdp)
{
    int rc = 0;
    int fd = -1;

    if (*firstlink == NULL) {

	rc = fsmOpen(&fd, dirfd, fp->fpath);

	if (fp->sb.st_nlink > 1) {
	    *firstlink = fp;
	    *firstlinkfile = fd;
	}
    } else {

	if (*firstlink != fp) {
	    rc = fsmLink(dirfd, (*firstlink)->fpath, dirfd, fp->fpath);
	}
	fd = *firstlinkfile;
    }


    if (rpmfiArchiveHasContent(fi)) {
	if (!rc)
	    rc = fsmUnpack(fi, fd, psm, nodigest);

	if (*firstlink) {
	    fp->setmeta = 1;
	    *firstlink = NULL;
	    *firstlinkfile = -1;
	}
    }
    *fdp = fd;

    return rc;
}
