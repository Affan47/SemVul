_dxf_initmessages(void)
{
    char *file, *s, name[100];
    int fd, mno, size;

    if (state)
	return OK;

#if pgcc
    atexit(DXqflush);
#endif


    state = (struct state *) DXAllocateZero(sizeof(struct state));
    if (!state)
	return ERROR;
    state->error_exit = 1;
    state->trace = 1;
    state->translate = 1;
#ifdef DEBUGGED
    DXEnableDebug("M", 1);
#endif
    if (!_dxf_initmemqueue())
	return ERROR;


    file = getenv("DXMESSAGES");
    if (file)
	sprintf(name, "%s", file);
    else {
	char *root = getenv("DXEXECROOT");
	if (!root) root = getenv("DXROOT");
	if (!root) root = "/usr/share/dx";
	sprintf(name, "%s/lib/messages", root);
    }
    fd = open(name, O_RDONLY);
    if (fd<0) {
	DXWarning("message file %s could not be opened", name);
	state->translate = 0;
	return OK;
    }
    size = lseek(fd, 0, 2);
    lseek(fd, 0, 0);
    state->buf = DXAllocate(size+1);
    if (!state->buf)
	return ERROR;
    if (read(fd, state->buf, size) < size) {
	DXWarning("message file %s could not be read", name);
	state->translate = 0;
	close(fd);
	return OK;
    }
    close(fd);
    state->buf[size] = '\0';
    s = state->buf;
    while (*s!='#' && *s)
	s++;
    while (*s) {
	*s = '\0';
	s++;
	mno = atoi(s);
	if (mno >= state->alloc) {
	    int n = 2*mno + 1;
	    char **m = (char **) DXReAllocate((Pointer)state->messages,
					   n * sizeof(char*));
	    if (!m)
		return ERROR;
	    state->messages = m;
	    state->alloc = n;
	}
	while ('0'<=*s && *s<='9')
	    s++;
	while (*s==' ' || *s=='\t' || *s=='\n')
	    s++;
	state->messages[mno] = s;
	if (mno > state->nmessages)
	    state->nmessages = mno;
	while (*s!='#' && *s) {
	    if (*s=='\n')
		*s = ' ';
	    s++;
	}
    }
    return OK;
}
