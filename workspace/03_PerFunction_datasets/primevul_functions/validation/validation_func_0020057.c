static void news2mail(message_data_t *msg)
{
    struct buf attrib = BUF_INITIALIZER;
    int n, r;
    FILE *sm;
    static strarray_t smbuf = STRARRAY_INITIALIZER;
    static int smbuf_basic_count;
    int sm_stat;
    pid_t sm_pid;
    char buf[4096], to[1024] = "";

    if (!smbuf.count) {
	strarray_append(&smbuf, "sendmail");
	strarray_append(&smbuf, "-i");
	strarray_append(&smbuf, "-f");
	strarray_append(&smbuf, "<>");
	strarray_append(&smbuf, "--");
	smbuf_basic_count = smbuf.count;
    }

    for (n = 0; n < msg->rcpt.count ; n++) {

	buf_free(&attrib);
	r = annotatemore_lookup(msg->rcpt.data[n],
				"/vendor/cmu/cyrus-imapd/news2mail", "",
				&attrib);
	if (r) continue;


	if (attrib.s) {
	    strarray_append(&smbuf, buf_cstring(&attrib));

	    if (to[0]) strlcat(to, ", ", sizeof(to));
	    strlcat(to, buf_cstring(&attrib), sizeof(to));
	}
    }
    buf_free(&attrib);


    if (smbuf.count > smbuf_basic_count) {
	sm_pid = open_sendmail((const char **)smbuf.data, &sm);

	if (!sm)
	    syslog(LOG_ERR, "news2mail: could not spawn sendmail process");
	else {
	    int body = 0, skip, found_to = 0;

	    rewind(msg->f);

	    while (fgets(buf, sizeof(buf), msg->f)) {
		if (!body && buf[0] == '\r' && buf[1] == '\n') {

		    body = 1;


		    if (!found_to) fprintf(sm, "To: %s\r\n", to);
		}

		skip = 0;
		if (!body) {

		    if (!strncasecmp(buf, "Newsgroups:", 11)) {

			fprintf(sm, "X-");
		    } else if (!strncasecmp(buf, "Xref:", 5) ||
			       !strncasecmp(buf, "Path:", 5) ||
			       !strncasecmp(buf, "NNTP-Posting-", 13)) {

			skip = 1;
		    } else if (!strncasecmp(buf, "To:", 3)) {


			fprintf(sm, "To: %s,\r\n", to);

			memset(buf, ' ', 3);
			found_to = 1;
		    } else if (!strncasecmp(buf, "Reply-To:", 9)) {

			if (!strip_post_addresses(buf+9)) skip = 1;
		    }
		}

		do {
		    if (!skip) fprintf(sm, "%s", buf);
		} while (buf[strlen(buf)-1] != '\n' &&
			 fgets(buf, sizeof(buf), msg->f));
	    }


	    if (buf[strlen(buf)-1] != '\n') fprintf(sm, "\r\n");

	    fclose(sm);
	    while (waitpid(sm_pid, &sm_stat, 0) < 0);

	    if (sm_stat)
		syslog(LOG_ERR, "news2mail failed: %s",
		       sendmail_errstr(sm_stat));
	}


	strarray_truncate(&smbuf, smbuf_basic_count);
    }

    return;
}
