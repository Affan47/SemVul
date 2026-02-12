SCTP_STATIC int sctp_seqpacket_listen(struct sock *sk, int backlog)
{
	struct sctp_sock *sp = sctp_sk(sk);
	struct sctp_endpoint *ep = sp->ep;


	if (!sctp_style(sk, UDP))
		return -EINVAL;


	if (!backlog) {
		if (sctp_sstate(sk, CLOSED))
			return 0;

		sctp_unhash_endpoint(ep);
		sk->sk_state = SCTP_SS_CLOSED;
		return 0;
	}


	if (sctp_sstate(sk, LISTENING))
		return 0;


	sk->sk_state = SCTP_SS_LISTENING;
	if (!ep->base.bind_addr.port) {
		if (sctp_autobind(sk))
			return -EAGAIN;
	} else {
		if (sctp_get_port(sk, inet_sk(sk)->num)) {
			sk->sk_state = SCTP_SS_CLOSED;
			return -EADDRINUSE;
		}
		sctp_sk(sk)->bind_hash->fastreuse = 0;
	}

	sctp_hash_endpoint(ep);
	return 0;
}
