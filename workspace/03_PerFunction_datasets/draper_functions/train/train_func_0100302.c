run_fwd_callbacks(struct sip_msg *req, char *buf, int len,
			struct socket_info* send_sock, int proto, union sockaddr_union *to)
{
	struct fwd_callback *cbp;
	str buffer;

	buffer.len = len;
	buffer.s = buf;

	for ( cbp=fwdcb_hl ; cbp ; cbp=cbp->next ) {
		LM_DBG("FWD callback entered\n");
		cbp->callback( req, &buffer, send_sock, proto, to);
	}
}
