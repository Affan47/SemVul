smf_initfile(struct smf_sc *sc, const char *size)
{
	sc->filesize = STV_FileSize(sc->fd, size, &sc->pagesize, "-sfile");

	AZ(ftruncate(sc->fd, (off_t)sc->filesize));


}
