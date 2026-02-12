parseURL(char *url, ParsedURL *p_url, ParsedURL *current)
{
    char *p, *q, *qq;
    Str tmp;

    url = url_quote(url);

    p = url;
    copyParsedURL(p_url, NULL);
    p_url->scheme = SCM_MISSING;


    if (*url == '\0' || *url == '#') {
	if (current)
	    copyParsedURL(p_url, current);
	goto do_label;
    }
#if defined( __EMX__ ) || defined( __CYGWIN__ )
    if (!strncasecmp(url, "file://localhost/", 17)) {
	p_url->scheme = SCM_LOCAL;
	p += 17 - 1;
	url += 17 - 1;
    }
#endif
#ifdef SUPPORT_DOS_DRIVE_PREFIX
    if (IS_ALPHA(*p) && (p[1] == ':' || p[1] == '|')) {
	p_url->scheme = SCM_LOCAL;
	goto analyze_file;
    }
#endif

    p_url->scheme = getURLScheme(&p);
    if (p_url->scheme == SCM_MISSING) {


	if (current) {
	    switch (current->scheme) {
	    case SCM_LOCAL:
	    case SCM_LOCAL_CGI:
		p_url->scheme = SCM_LOCAL;
		break;
	    case SCM_FTP:
	    case SCM_FTPDIR:
		p_url->scheme = SCM_FTP;
		break;
#ifdef USE_NNTP
	    case SCM_NNTP:
	    case SCM_NNTP_GROUP:
		p_url->scheme = SCM_NNTP;
		break;
	    case SCM_NEWS:
	    case SCM_NEWS_GROUP:
		p_url->scheme = SCM_NEWS;
		break;
#endif
	    default:
		p_url->scheme = current->scheme;
		break;
	    }
	}
	else
	    p_url->scheme = SCM_LOCAL;
	p = url;
	if (!strncmp(p, "//", 2)) {


	    p += 2;
	    goto analyze_url;
	}

	goto analyze_file;
    }

    if (p_url->scheme == SCM_UNKNOWN) {
	p_url->file = allocStr(url, -1);
	return;
    }

    if (p[0] != '/' || p[1] != '/') {
	p_url->host = NULL;
	if (p_url->scheme != SCM_UNKNOWN)
	    p_url->port = DefaultPort[p_url->scheme];
	else
	    p_url->port = 0;
	goto analyze_file;
    }

    if (p_url->scheme == SCM_LOCAL) {
#ifdef __EMX__
	p += 2;
	goto analyze_file;
#else
	if (p[2] == '/' || p[2] == '~'

#ifdef SUPPORT_DOS_DRIVE_PREFIX
	    || (IS_ALPHA(p[2]) && (p[3] == ':' || p[3] == '|'))

#endif
	    ) {
	    p += 2;
	    goto analyze_file;
	}
#endif
    }
    p += 2;

  analyze_url:
    q = p;
#ifdef INET6
    if (*q == '[') {
	p++;
	while (IS_XDIGIT(*p) || *p == ':' || *p == '.')
	    p++;
	if (*p != ']' || (*(p + 1) && strchr(":/?#", *(p + 1)) == NULL))
	    p = q;
    }
#endif
    while (*p && strchr(":/@?#", *p) == NULL)
	p++;
    switch (*p) {
    case ':':


	qq = q;
	q = ++p;
	while (*p && strchr("@/?#", *p) == NULL)
	    p++;
	if (*p == '@') {

	    p_url->user = copyPath(qq, q - 1 - qq, COPYPATH_SPC_IGNORE);
	    p_url->pass = copyPath(q, p - q, COPYPATH_SPC_ALLOW);
	    p++;
	    goto analyze_url;
	}

	p_url->host = copyPath(qq, q - 1 - qq,
			       COPYPATH_SPC_IGNORE | COPYPATH_LOWERCASE);
	tmp = Strnew_charp_n(q, p - q);
	p_url->port = atoi(tmp->ptr);

	break;
    case '@':

	p_url->user = copyPath(q, p - q, COPYPATH_SPC_IGNORE);
	p++;
	goto analyze_url;
    case '\0':

    case '/':
    case '?':
    case '#':
	p_url->host = copyPath(q, p - q,
			       COPYPATH_SPC_IGNORE | COPYPATH_LOWERCASE);
	if (p_url->scheme != SCM_UNKNOWN)
	    p_url->port = DefaultPort[p_url->scheme];
	else
	    p_url->port = 0;
	break;
    }
  analyze_file:
#ifndef SUPPORT_NETBIOS_SHARE
    if (p_url->scheme == SCM_LOCAL && p_url->user == NULL &&
	p_url->host != NULL && *p_url->host != '\0' &&
	strcmp(p_url->host, "localhost")) {


	p_url->scheme = SCM_FTP;
	if (p_url->port == 0)
	    p_url->port = DefaultPort[SCM_FTP];
    }
#endif
    if ((*p == '\0' || *p == '#' || *p == '?') && p_url->host == NULL) {
	p_url->file = "";
	goto do_query;
    }
#ifdef SUPPORT_DOS_DRIVE_PREFIX
    if (p_url->scheme == SCM_LOCAL) {
	q = p;
	if (*q == '/')
	    q++;
	if (IS_ALPHA(q[0]) && (q[1] == ':' || q[1] == '|')) {
	    if (q[1] == '|') {
		p = allocStr(q, -1);
		p[1] = ':';
	    }
	    else
		p = q;
	}
    }
#endif

    q = p;
#ifdef USE_GOPHER
    if (p_url->scheme == SCM_GOPHER) {
	if (*q == '/')
	    q++;
	if (*q && q[0] != '/' && q[1] != '/' && q[2] == '/')
	    q++;
    }
#endif
    if (*p == '/')
	p++;
    if (*p == '\0' || *p == '#' || *p == '?') {
	p_url->file = DefaultFile(p_url->scheme);
	goto do_query;
    }
#ifdef USE_GOPHER
    if (p_url->scheme == SCM_GOPHER && *p == 'R') {
	p++;
	tmp = Strnew();
	Strcat_char(tmp, *(p++));
	while (*p && *p != '/')
	    p++;
	Strcat_charp(tmp, p);
	while (*p)
	    p++;
	p_url->file = copyPath(tmp->ptr, -1, COPYPATH_SPC_IGNORE);
    }
    else
#endif
    {
	char *cgi = strchr(p, '?');
      again:
	while (*p && *p != '#' && p != cgi)
	    p++;
	if (*p == '#' && p_url->scheme == SCM_LOCAL) {


	    if (p > q && *(p - 1) == '/' && (cgi == NULL || p < cgi)) {


		p++;
		goto again;
	    }
	    else if (*(p + 1) == '\0') {


		p++;
	    }
	}
	if (p_url->scheme == SCM_LOCAL || p_url->scheme == SCM_MISSING)
	    p_url->file = copyPath(q, p - q, COPYPATH_SPC_ALLOW);
	else
	    p_url->file = copyPath(q, p - q, COPYPATH_SPC_IGNORE);
    }

  do_query:
    if (*p == '?') {
	q = ++p;
	while (*p && *p != '#')
	    p++;
	p_url->query = copyPath(q, p - q, COPYPATH_SPC_ALLOW);
    }
  do_label:
    if (p_url->scheme == SCM_MISSING) {
	p_url->scheme = SCM_LOCAL;
	p_url->file = allocStr(p, -1);
	p_url->label = NULL;
    }
    else if (*p == '#')
	p_url->label = allocStr(p + 1, -1);
    else
	p_url->label = NULL;
}
