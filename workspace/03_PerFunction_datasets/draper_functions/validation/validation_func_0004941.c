mfreopen(const char *path, const char *mode_str, FILE *fp) {
    mFILE *mf;
    int r = 0, w = 0, a = 0, b = 0, x = 0, mode = 0;


    if (strchr(mode_str, 'r'))
	r = 1, mode |= MF_READ;
    if (strchr(mode_str, 'w'))
	w = 1, mode |= MF_WRITE | MF_TRUNC;
    if (strchr(mode_str, 'a'))
	w = a = 1, mode |= MF_WRITE | MF_APPEND;
    if (strchr(mode_str, 'b'))
	b = 1, mode |= MF_BINARY;
    if (strchr(mode_str, 'x'))
	x = 1;
    if (strchr(mode_str, '+')) {
        w = 1, mode |= MF_READ | MF_WRITE;
	if (a)
	    r = 1;
    }

    if (r) {
	mf = mfcreate(NULL, 0);
	if (!(mode & MF_TRUNC)) {
	    mf->data = mfload(fp, path, &mf->size, b);
	    mf->alloced = mf->size;
	    if (!a)
		fseek(fp, 0, SEEK_SET);
	}
    } else if (w) {

	mf = mfcreate(NULL, 0);
    } else {
        fprintf(stderr, "Must specify either r, w or a for mode\n");
        return NULL;
    }
    mf->fp = fp;
    mf->mode = mode;

    if (x) {
	if (ftello(fp) != -1) {
	    mf->mode |= MF_MODEX;
	}
    }

    if (a) {
	mf->flush_pos = mf->size;
	fseek(fp, 0, SEEK_END);
    }

    return mf;
}
