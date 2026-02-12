static int sctp_setsockopt_bindx(struct sock *sk, struct sockaddr *addrs,
				 int addrs_size, int op)
{
	int err;
	int addrcnt = 0;
	int walk_size = 0;
	struct sockaddr *sa_addr;
	void *addr_buf = addrs;
	struct sctp_af *af;

	pr_debug("%s: sk:%p addrs:%p addrs_size:%d opt:%d\n",
		 __func__, sk, addr_buf, addrs_size, op);

	if (unlikely(addrs_size <= 0))
		return -EINVAL;


	while (walk_size < addrs_size) {
		if (walk_size + sizeof(sa_family_t) > addrs_size)
			return -EINVAL;

		sa_addr = addr_buf;
		af = sctp_get_af_specific(sa_addr->sa_family);


		if (!af || (walk_size + af->sockaddr_len) > addrs_size)
			return -EINVAL;
		addrcnt++;
		addr_buf += af->sockaddr_len;
		walk_size += af->sockaddr_len;
	}


	switch (op) {
	case SCTP_BINDX_ADD_ADDR:

		err = security_sctp_bind_connect(sk, SCTP_SOCKOPT_BINDX_ADD,
						 addrs, addrs_size);
		if (err)
			return err;
		err = sctp_bindx_add(sk, addrs, addrcnt);
		if (err)
			return err;
		return sctp_send_asconf_add_ip(sk, addrs, addrcnt);
	case SCTP_BINDX_REM_ADDR:
		err = sctp_bindx_rem(sk, addrs, addrcnt);
		if (err)
			return err;
		return sctp_send_asconf_del_ip(sk, addrs, addrcnt);

	default:
		return -EINVAL;
	}
}
