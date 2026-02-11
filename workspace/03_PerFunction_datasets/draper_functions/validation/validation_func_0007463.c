mboxname_tointernal(struct namespace *namespace, const char *name,
			       const char *userid, char *result)
{
    char *cp;
    char *atp;
    char *mbresult;
    int userlen, domainlen = 0, namelen;


    result[0] = '\0';
    result[MAX_MAILBOX_BUFFER-1] = '\0';

    userlen = userid ? strlen(userid) : 0;
    namelen = strlen(name);

    if (config_virtdomains) {
	if (userid && (cp = strrchr(userid, '@'))) {

	    userlen = cp - userid;

	    if (!(config_defdomain && !strcasecmp(config_defdomain, cp+1))) {
		domainlen = strlen(cp+1)+1;
		snprintf(result, MAX_MAILBOX_BUFFER, "%s!", cp+1);
	    }
	}
	if ((cp = strrchr(name, '@'))) {

	    namelen = cp - name;

	    if (config_defdomain && !strcasecmp(config_defdomain, cp+1)) {
		if (domainlen) {

		    return IMAP_MAILBOX_BADNAME;
		}

	    }
	    else {
		if ((!domainlen && !namespace->isadmin) ||
		    (domainlen && strcasecmp(userid+userlen, cp))) {


		    return IMAP_MAILBOX_BADNAME;
		}
		domainlen = strlen(cp+1)+1;
		snprintf(result, MAX_MAILBOX_BUFFER, "%s!", cp+1);
	    }

	    atp = strchr(name, '@');
	    if (atp && atp != cp) {

		return IMAP_MAILBOX_BADNAME;
	    }
	}


    }

    mbresult = result + domainlen;


    if ((name[0] == 'i' || name[0] == 'I') &&
	!strncasecmp(name, "inbox", 5) &&
	(namelen == 5 || name[5] == namespace->hier_sep)) {

	if (!userid || ((cp = strchr(userid, namespace->hier_sep)) &&
			(cp - userid < userlen))) {
	    return IMAP_MAILBOX_BADNAME;
	}

	snprintf(mbresult, MAX_MAILBOX_BUFFER - domainlen,
		 "user.%.*s%.*s", userlen, userid, namelen-5, name+5);


	mboxname_hiersep_tointernal(namespace, mbresult+5+userlen, 0);
    }

    else {

	snprintf(mbresult, MAX_MAILBOX_BUFFER - domainlen,
		 "%.*s", namelen, name);


	mboxname_hiersep_tointernal(namespace, mbresult, 0);
    }

    if (result[MAX_MAILBOX_BUFFER-1] != '\0') {
	syslog(LOG_ERR, "IOERROR: long mailbox name attempt: %s", name);
	return IMAP_MAILBOX_BADNAME;
    }
    return 0;
}
