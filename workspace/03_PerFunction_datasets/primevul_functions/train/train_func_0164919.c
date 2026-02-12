SCTP_STATIC int sctp_do_peeloff(struct sctp_association *asoc,
				struct socket **sockp)
{
	struct sock *sk = asoc->base.sk;
	struct socket *sock;
	struct inet_sock *inetsk;
	struct sctp_af *af;
	int err = 0;


	if (!sctp_style(sk, UDP))
		return -EINVAL;


	err = sock_create(sk->sk_family, SOCK_SEQPACKET, IPPROTO_SCTP, &sock);
	if (err < 0)
		return err;


	sctp_sock_migrate(sk, sock->sk, asoc, SCTP_SOCKET_UDP_HIGH_BANDWIDTH);


	af = sctp_get_af_specific(asoc->peer.primary_addr.sa.sa_family);
	af->to_sk_daddr(&asoc->peer.primary_addr, sk);
	inetsk = inet_sk(sock->sk);
	inetsk->id = asoc->next_tsn ^ jiffies;

	*sockp = sock;

	return err;
}
