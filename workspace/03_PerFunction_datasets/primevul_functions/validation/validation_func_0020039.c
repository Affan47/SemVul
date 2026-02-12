static void parse_groups(const char *groups, message_data_t *msg)
{
    const char *p;
    char *rcpt = NULL;
    char *buf = xstrdup(groups);
    const char sep[] = ", \t";

    for (p = strtok(buf, sep) ; p ; p = strtok(NULL, sep)) {

	free(rcpt);
	rcpt = strconcat(newsprefix, p, (char *)NULL);


	if (!is_newsgroup(rcpt)) continue;


	if (!mlookup(rcpt, NULL)) {
	    strarray_appendm(&msg->rcpt, rcpt);
	    rcpt = NULL;
	}
    }
    free(rcpt);
    free(buf);
}
