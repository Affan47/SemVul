logfile_mod_stdio_rotate(Logfile * lf)
{
#ifdef S_ISREG

    struct stat sb;
#endif

    int i;
    char from[MAXPATHLEN];
    char to[MAXPATHLEN];
    l_stdio_t *ll = (l_stdio_t *) lf->data;
    assert(lf->path);

#ifdef S_ISREG

    if (stat(lf->path, &sb) == 0)
	if (S_ISREG(sb.st_mode) == 0)
	    return;

#endif

    debug(0, 1) ("logfileRotate (stdio): %s\n", lf->path);


    for (i = Config.Log.rotateNumber; i > 1;) {
	i--;
	snprintf(from, MAXPATHLEN, "%s.%d", lf->path, i - 1);
	snprintf(to, MAXPATHLEN, "%s.%d", lf->path, i);
	xrename(from, to);
    }


    logfileFlush(lf);

    file_close(ll->fd);

    if (Config.Log.rotateNumber > 0) {
	snprintf(to, MAXPATHLEN, "%s.%d", lf->path, 0);
	xrename(lf->path, to);
    }

    ll->fd = file_open(lf->path, O_WRONLY | O_CREAT | O_TEXT);

    if (DISK_ERROR == ll->fd && lf->flags.fatal) {
	debug(50, 1) ("logfileRotate (stdio): %s: %s\n", lf->path, xstrerror());
	fatalf("Cannot open %s: %s", lf->path, xstrerror());
    }
}
