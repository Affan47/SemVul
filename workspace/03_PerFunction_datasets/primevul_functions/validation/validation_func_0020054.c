static int list_cb(char *name, int matchlen,
		   int maycreate __attribute__((unused)), void *rock)
{
    static char lastname[MAX_MAILBOX_BUFFER];
    struct list_rock *lrock = (struct list_rock *) rock;
    struct wildmat *wild;


    if (!name) {
	lastname[0] = '\0';
	return 0;
    }


    if (!is_newsgroup(name)) return 0;


    if (matchlen == (int) strlen(lastname) &&
	!strncmp(name, lastname, matchlen)) return 0;

    strncpy(lastname, name, matchlen);
    lastname[matchlen] = '\0';


    wild = lrock->wild;
    while (wild->pat && wildmat(name, wild->pat) != 1) wild++;


    if (!wild->pat || wild->not) return 0;

    return lrock->proc(name, lrock);
}
