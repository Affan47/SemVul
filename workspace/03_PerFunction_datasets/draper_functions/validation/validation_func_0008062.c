virtual_in(IN *in)
{
    const struct atmtcp_hdr *hdr = (struct atmtcp_hdr *) in->buf;
    int got;

    got = read(in->fd,in->buf,MAX_PACKET);
    if (got < 0) {
	perror("virtual interface");
	exit(1);
    }
    if (!got) exit(0);
    if (got < sizeof(struct atmtcp_hdr)) {
	fprintf(stderr,"kernel message too small (%d)\n",got);
	exit(1);
    }
    if (ntohl(hdr->length) == ATMTCP_HDR_MAGIC) {
	if (got < sizeof(struct atmtcp_control)) {
	    fprintf(stderr,"invalid control message\n");
	    exit(1);
	}
	control(in->link,(struct atmtcp_control *) in->buf);
	virtual_do_send(in->fd,hdr,sizeof(struct atmtcp_control));
	return;
    }
    if (got != sizeof(struct atmtcp_hdr)+ntohl(hdr->length)) {
	fprintf(stderr,"invalid kernel message\n");
	exit(1);
    }
    emit(in->link,hdr,got);
}
