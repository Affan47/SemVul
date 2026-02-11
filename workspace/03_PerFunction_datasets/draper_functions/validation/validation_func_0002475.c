read_message_header(ne_request *req, char *buf, size_t buflen)
{
    ssize_t n;
    ne_socket *sock = req->session->socket;

    n = ne_sock_readline(sock, buf, buflen);
    if (n <= 0)
	return aborted(req, _("Error reading response headers"), n);
    NE_DEBUG(NE_DBG_HTTP, "[hdr] %s", buf);

    strip_eol(buf, &n);

    if (n == 0) {
	NE_DEBUG(NE_DBG_HTTP, "End of headers.\n");
	return NE_OK;
    }

    buf += n;
    buflen -= n;

    while (buflen > 0) {
	char ch;


	SOCK_ERR(req, ne_sock_peek(sock, &ch, 1),
		 _("Error reading response headers"));

	if (ch != ' ' && ch != '\t') {

	    return NE_RETRY;
	}


	n = ne_sock_readline(sock, buf, buflen);
	if (n <= 0) {
	    return aborted(req, _("Error reading response headers"), n);
	}

	NE_DEBUG(NE_DBG_HTTP, "[cont] %s", buf);

	strip_eol(buf, &n);


	if (n) buf[0] = ' ';


	buf += n;
	buflen -= n;
    }

    ne_set_error(req->session, _("Response header too long"));
    return NE_ERROR;
}
