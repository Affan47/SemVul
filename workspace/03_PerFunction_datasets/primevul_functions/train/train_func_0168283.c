static void parse_url(const char *src_url, struct host_info *h)
{
	char *url, *p, *sp;

	free(h->allocated);
	h->allocated = url = xstrdup(src_url);

	h->protocol = P_FTP;
	p = strstr(url, "://");
	if (p) {
		*p = '\0';
		h->host = p + 3;
		if (strcmp(url, P_FTP) == 0) {
			h->port = bb_lookup_std_port(P_FTP, "tcp", 21);
		} else
#if SSL_SUPPORTED
# if ENABLE_FEATURE_WGET_HTTPS
		if (strcmp(url, P_FTPS) == 0) {
			h->port = bb_lookup_std_port(P_FTPS, "tcp", 990);
			h->protocol = P_FTPS;
		} else
# endif
		if (strcmp(url, P_HTTPS) == 0) {
			h->port = bb_lookup_std_port(P_HTTPS, "tcp", 443);
			h->protocol = P_HTTPS;
		} else
#endif
		if (strcmp(url, P_HTTP) == 0) {
 http:
			h->port = bb_lookup_std_port(P_HTTP, "tcp", 80);
			h->protocol = P_HTTP;
		} else {
			*p = ':';
			bb_error_msg_and_die("not an http or ftp url: %s", url);
		}
	} else {

		h->host = url;
		goto http;
	}


	sp = strchr(h->host, '/');
	p = strchr(h->host, '?'); if (!sp || (p && sp > p)) sp = p;
	p = strchr(h->host, '#'); if (!sp || (p && sp > p)) sp = p;
	if (!sp) {
		h->path = "";
	} else if (*sp == '/') {
		*sp = '\0';
		h->path = sp + 1;
	} else {


		*sp++ = '\0';
		h->path = sp;
	}

	sp = strrchr(h->host, '@');
	if (sp != NULL) {


		*sp = '\0';
		free(h->user);
		h->user = xstrdup(percent_decode_in_place(h->host,  0));
		h->host = sp + 1;
	}


}
