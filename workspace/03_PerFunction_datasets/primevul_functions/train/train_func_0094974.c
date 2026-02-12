process_request(isc_httpd_t *httpd, isc_region_t *region, size_t *buflen) {
	char *s = NULL, *p = NULL, *urlend = NULL;
	const char *content_length = NULL;
	size_t limit = sizeof(httpd->recvbuf) - httpd->recvlen - 1;
	size_t len = region->length;
	size_t clen = 0;
	int delim;
	bool truncated = false;

	if (len > limit) {
		len = limit;
		truncated = true;
	}

	if (len > 0U) {
		if (httpd->truncated) {
			return (ISC_R_NOSPACE);
		}
		memmove(httpd->recvbuf + httpd->recvlen, region->base, len);
		httpd->recvlen += len;
		httpd->recvbuf[httpd->recvlen] = 0;
		isc_region_consume(region, len);
	}
	if (truncated) {
		httpd->truncated = true;
	}
	httpd->headers = NULL;
	*buflen = httpd->recvlen;


	s = strstr(httpd->recvbuf, "\r\n\r\n");
	delim = 2;
	if (s == NULL) {
		s = strstr(httpd->recvbuf, "\n\n");
		delim = 1;
		if (s == NULL) {
			return (httpd->truncated ? ISC_R_NOSPACE
						 : ISC_R_NOTFOUND);
		}
		httpd->consume = s + 2 - httpd->recvbuf;
	} else {
		httpd->consume = s + 4 - httpd->recvbuf;
	}


	s[delim] = 0;


	if (strncmp(httpd->recvbuf, "GET ", 4) == 0) {
		httpd->method = METHOD_GET;
		p = httpd->recvbuf + 4;
	} else if (strncmp(httpd->recvbuf, "POST ", 5) == 0) {
		httpd->method = METHOD_POST;
		p = httpd->recvbuf + 5;
	} else {
		return (ISC_R_RANGE);
	}


	s = p;
	while (LENGTHOK(s) && BUFLENOK(s) &&
	       (*s != '\n' && *s != '\r' && *s != '\0' && *s != ' '))
	{
		s++;
	}
	if (!LENGTHOK(s)) {
		return (ISC_R_NOTFOUND);
	}
	if (!BUFLENOK(s)) {
		return (ISC_R_NOMEMORY);
	}
	urlend = s;


	if (strncmp(p, "http://", 7) == 0 || strncmp(p, "https://", 8) == 0) {

		while (*p != '/' && *p != 0) {
			p++;
		}
		if (*p == 0) {
			return (ISC_R_RANGE);
		}
		p++;

		while (*p != '/' && *p != 0) {
			p++;
		}
		if (*p == 0) {
			return (ISC_R_RANGE);
		}
		p++;

		while (*p != '/' && *p != 0) {
			p++;
		}
		if (*p == 0) {
			p--;
			*p = '/';
		}
	}

	httpd->url = p;
	p = s + 1;
	s = p;


	httpd->querystring = strchr(httpd->url, '?');
	if (httpd->querystring != NULL) {
		*(httpd->querystring) = 0;
		httpd->querystring++;
	}


	while (LENGTHOK(s) && BUFLENOK(s) &&
	       (*s != '\n' && *s != '\r' && *s != '\0')) {
		s++;
	}
	if (!LENGTHOK(s)) {
		return (ISC_R_NOTFOUND);
	}
	if (!BUFLENOK(s)) {
		return (ISC_R_NOMEMORY);
	}


	if (strncmp(s, delim == 1 ? "\n" : "\r\n", delim) != 0) {
		return (ISC_R_RANGE);
	}
	*s = 0;
	if ((strncmp(p, "HTTP/1.0", 8) != 0) &&
	    (strncmp(p, "HTTP/1.1", 8) != 0)) {
		return (ISC_R_RANGE);
	}
	httpd->protocol = p;
	p = s + delim;
	s = p;

	httpd->headers = s;

	if (!have_header(httpd, "Content-Length:", NULL, NULL, &content_length))
	{

		if (httpd->method == METHOD_POST) {
			return (ISC_R_BADNUMBER);
		}
	} else {
		INSIST(content_length != NULL);

		clen = (size_t)strtoul(content_length, NULL, 10);
		if (clen == ULONG_MAX) {

			return (ISC_R_BADNUMBER);
		}
		if (httpd->recvlen < httpd->consume + clen) {

			return (ISC_R_NOTFOUND);
		}


		httpd->consume += clen;
	}

	if (have_header(httpd, "Connection:", "close", ", \t\r\n", NULL)) {
		httpd->flags |= HTTPD_CLOSE;
	}

	if (have_header(httpd, "Host:", NULL, NULL, NULL)) {
		httpd->flags |= HTTPD_FOUNDHOST;
	}

	if (strncmp(httpd->protocol, "HTTP/1.0", 8) == 0) {
		if (have_header(httpd, "Connection:", "Keep-Alive", ", \t\r\n",
				NULL)) {
			httpd->flags |= HTTPD_KEEPALIVE;
		} else {
			httpd->flags |= HTTPD_CLOSE;
		}
	}


#ifdef HAVE_ZLIB
	if (have_header(httpd, "Accept-Encoding:", "deflate", ";, \t\r\n",
			NULL)) {
		httpd->flags |= HTTPD_ACCEPT_DEFLATE;
	}
#endif


	if (strcmp(httpd->protocol, "HTTP/1.1") == 0 &&
	    ((httpd->flags & HTTPD_FOUNDHOST) == 0))
	{
		return (ISC_R_RANGE);
	}


	*urlend = 0;

	return (ISC_R_SUCCESS);
}
