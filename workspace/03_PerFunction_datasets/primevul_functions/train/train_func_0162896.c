http1_body_status(const struct http *hp, struct http_conn *htc, int request)
{
	ssize_t cl;
	const char *b;

	CHECK_OBJ_NOTNULL(htc, HTTP_CONN_MAGIC);
	CHECK_OBJ_NOTNULL(hp, HTTP_MAGIC);

	htc->content_length = -1;

	cl = http_GetContentLength(hp);
	if (cl == -2)
		return (BS_ERROR);
	if (http_GetHdr(hp, H_Transfer_Encoding, &b)) {
		if (strcasecmp(b, "chunked"))
			return (BS_ERROR);
		if (cl != -1) {


			return (BS_ERROR);
		}
		return (BS_CHUNKED);
	}
	if (cl >= 0) {
		htc->content_length = cl;
		return (cl == 0 ? BS_NONE : BS_LENGTH);
	}

	if (hp->protover == 11 && request)
		return (BS_NONE);

	if (http_HdrIs(hp, H_Connection, "keep-alive")) {


		return (BS_NONE);
	}


	return (BS_EOF);
}
