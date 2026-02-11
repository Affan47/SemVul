at_recipok_limit(char *cmd)
{
    char domain_buf[MAX_DOMAIN_LEN];
    char const *ptr = cmd;
    char *out = domain_buf;
    int len = 0;
    int count = 0;
    Slave *s;

    while(*ptr && (*ptr != '@')) ptr++;


    if (*ptr != '@') return 0;

    ptr++;
    while(*ptr && *ptr != '>' && *ptr != ' ') {
	len++;
	*out++ = *ptr++;
	if (len >= MAX_DOMAIN_LEN - 1) break;
    }
    *out = 0;


    s = Slaves[STATE_BUSY];
    while(s) {
	if (s->cmd == RECIPOK_CMD &&
	    !strcasecmp(s->domain, domain_buf)) {
	    count++;
	    if (count >= Settings.maxRecipokPerDomain) {
		if (DOLOG) {
		    syslog(LOG_WARNING, "Hit per-domain recipok limit (%d) for domain %s", Settings.maxRecipokPerDomain, domain_buf);
		}
		return 1;
	    }
	}
	s = s->next;
    }
    return 0;
}
