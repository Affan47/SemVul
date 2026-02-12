static int __sctp_setsockopt_connectx(struct sock *sk, struct sockaddr *kaddrs,
				      int addrs_size, sctp_assoc_t *assoc_id)
{
	int err = 0, flags = 0;

	pr_debug("%s: sk:%p addrs:%p addrs_size:%d\n",
		 __func__, sk, kaddrs, addrs_size);


	if (unlikely(addrs_size < sizeof(sa_family_t)))
		return -EINVAL;


	err = security_sctp_bind_connect(sk, SCTP_SOCKOPT_CONNECTX,
					 (struct sockaddr *)kaddrs,
					  addrs_size);
	if (err)
		return err;


	if (sk->sk_socket->file)
		flags = sk->sk_socket->file->f_flags;

	return __sctp_connect(sk, kaddrs, addrs_size, flags, assoc_id);
}
