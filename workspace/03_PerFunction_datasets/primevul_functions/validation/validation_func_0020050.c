static int savemsg(message_data_t *m, FILE *f)
{
    struct stat sbuf;
    const char **body, **groups;
    int r, i;
    time_t now = time(NULL);
    static int post_count = 0;
    FILE *stagef = NULL;
    const char *skipheaders[] = {
	"Path",
	"Xref",
	"Reply-To",
	NULL
    };

    m->f = f;


    r = spool_fill_hdrcache(nntp_in, f, m->hdrcache, skipheaders);
    if (r) {


	spool_copy_msg(nntp_in, NULL);
	return r;
    }


    if ((body = spool_getheader(m->hdrcache, "path")) != NULL) {

	m->path = strconcat(config_servername, "!", body[0], (char *)NULL);
	spool_replace_header(xstrdup("Path"), xstrdup(m->path), m->hdrcache);
    } else {

	m->path = strconcat(config_servername, "!",
			    nntp_userid ? nntp_userid : "anonymous",
			    (char *)NULL);
	spool_cache_header(xstrdup("Path"), xstrdup(m->path), m->hdrcache);
    }
    fprintf(f, "Path: %s\r\n", m->path);


    if ((body = spool_getheader(m->hdrcache, "message-id")) != NULL) {
	m->id = xstrdup(body[0]);
    } else {

	pid_t p = getpid();

	m->id = xmalloc(40 + strlen(config_servername));
	sprintf(m->id, "<cmu-nntpd-%d-%d-%d@%s>", p, (int) now,
		post_count++, config_servername);
	fprintf(f, "Message-ID: %s\r\n", m->id);
	spool_cache_header(xstrdup("Message-ID"), xstrdup(m->id), m->hdrcache);
    }


    if ((body = spool_getheader(m->hdrcache, "date")) == NULL) {

	char datestr[RFC822_DATETIME_MAX+1];

	time_to_rfc822(now, datestr, sizeof(datestr));
	m->date = xstrdup(datestr);
	fprintf(f, "Date: %s\r\n", datestr);
	spool_cache_header(xstrdup("Date"), xstrdup(datestr), m->hdrcache);
    }
    else {
	m->date = xstrdup(body[0]);
    }


    if ((body = spool_getheader(m->hdrcache, "control")) != NULL) {
	size_t len;
	char *s;

	m->control = xstrdup(body[0]);


	len = strcspn(m->control, " \t\r\n");
	s = xmalloc(strlen(newsprefix) + 8 + len + 1);
	sprintf(s, "%scontrol.%.*s", newsprefix, (int) len, m->control);

	strarray_appendm(&m->rcpt, s);
    } else {
	m->control = NULL;


	if ((groups = spool_getheader(m->hdrcache, "newsgroups")) != NULL) {

	    parse_groups(groups[0], m);
	    if (!m->rcpt.count) {
		r = IMAP_MAILBOX_NONEXISTENT;
	    }
	    if (!r) {
		const char *newspostuser = config_getstring(IMAPOPT_NEWSPOSTUSER);

		body = spool_getheader(m->hdrcache, "reply-to");


		if (body || newspostuser) {
		    const char **postto, *p;
		    int fold = 0;
		    const char *sep = "";
		    char *replyto;
		    size_t n;
		    struct buf buf = BUF_INITIALIZER;

		    if (newspostuser) {


			postto = spool_getheader(m->hdrcache, "followup-to");
			if (!postto) postto = groups;

			if (body) {

			    buf_appendcstr(&buf, body[0]);
			    fold = buf.len+1;
			    sep = ", ";
			}
			for (p = postto[0];; p += n) {

			    while (p && *p &&
				   (Uisspace(*p) || *p == ',')) p++;
			    if (!p || !*p) break;


			    n = strcspn(p, ", \t");


			    buf_printf(&buf, "%s%s+%.*s",
					 sep, newspostuser, (int) n, p);

			    sep = ", ";
			}
			replyto = buf_release(&buf);
			if (body) {

			    spool_replace_header(xstrdup("Reply-To"), replyto,
					         m->hdrcache);
			} else {

			    spool_cache_header(xstrdup("Reply-To"), replyto,
					       m->hdrcache);
			}
		    } else {

			replyto = (char *) body[0];
		    }


		    fprintf(f, "Reply-To: ");
		    if (fold)
			fprintf(f, "%.*s\r\n\t", fold, replyto);
		    fprintf(f, "%s\r\n", replyto+fold);
		}
	    }
	} else {
	    r = NNTP_NO_NEWSGROUPS;
	}

	if (r) {


	    spool_copy_msg(nntp_in, NULL);
	    return r;
	}
    }

    fflush(f);
    if (ferror(f)) {
	return IMAP_IOERROR;
    }

    if (fstat(fileno(f), &sbuf) == -1) {
	return IMAP_IOERROR;
    }


    for (i = 0; !stagef && (i < m->rcpt.count); i++) {
	stagef = append_newstage(m->rcpt.data[i], now, 0, &stage);
    }

    if (stagef) {
	const char *base = 0;
	unsigned long size = 0;
	int n;


	map_refresh(fileno(f), 1, &base, &size, sbuf.st_size, "tmp", 0);
	n = retry_write(fileno(stagef), base, size);
	map_free(&base, &size);

	if (n == -1) {

	    fclose(stagef);
	    append_removestage(stage);
	    stage = NULL;
	    return IMAP_IOERROR;
	}
	else {

	    fclose(f);
	    m->f = f = stagef;
	}
    }


    r = spool_copy_msg(nntp_in, f);

    if (r) return r;

    fflush(f);
    if (ferror(f)) {
	return IMAP_IOERROR;
    }

    if (fstat(fileno(f), &sbuf) == -1) {
	return IMAP_IOERROR;
    }
    m->size = sbuf.st_size;
    m->data = prot_new(fileno(f), 0);

    return 0;
}
