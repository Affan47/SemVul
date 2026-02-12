void selinux_netlbl_inet_conn_established(struct sock *sk, u16 family)
{
	int rc;
	struct sk_security_struct *sksec = sk->sk_security;
	struct netlbl_lsm_secattr *secattr;
	struct inet_sock *sk_inet = inet_sk(sk);
	struct sockaddr_in addr;

	if (sksec->nlbl_state != NLBL_REQUIRE)
		return;

	secattr = selinux_netlbl_sock_genattr(sk);
	if (secattr == NULL)
		return;

	rc = netlbl_sock_setattr(sk, secattr);
	switch (rc) {
	case 0:
		sksec->nlbl_state = NLBL_LABELED;
		break;
	case -EDESTADDRREQ:


		if (family != PF_INET) {
			sksec->nlbl_state = NLBL_UNSET;
			return;
		}

		addr.sin_family = family;
		addr.sin_addr.s_addr = sk_inet->daddr;
		if (netlbl_conn_setattr(sk, (struct sockaddr *)&addr,
					secattr) != 0) {


			struct inet_connection_sock *sk_conn = inet_csk(sk);
			sk_conn->icsk_ext_hdr_len += 40 -
				      (sk_inet->opt ? sk_inet->opt->optlen : 0);
			sk_conn->icsk_sync_mss(sk, sk_conn->icsk_pmtu_cookie);

			sksec->nlbl_state = NLBL_REQSKB;
		} else
			sksec->nlbl_state = NLBL_CONNLABELED;
		break;
	default:


		break;
	}
}
