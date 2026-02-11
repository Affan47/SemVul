message_parse_header(hdr, ibuf)
char *hdr;
struct ibuf *ibuf;
{
    int len;
    char *hdrend;


    hdrend = hdr;
    do {
	hdrend = strchr(hdrend+1, '\n');
    } while (hdrend && (hdrend[1] == ' ' || hdrend[1] == '\t'));
    if (hdrend) {
	if (hdrend > hdr && hdrend[-1] == '\r') hdrend--;
    }
    else {
	hdrend = hdr + strlen(hdr);
    }


    len = hdrend - hdr;
    message_ibuf_ensure(ibuf, len+2);
    strncpy(ibuf->end, hdr, len);
    ibuf->end += len;
    *(ibuf->end)++ = '\r';
    *(ibuf->end)++ = '\n';
}
