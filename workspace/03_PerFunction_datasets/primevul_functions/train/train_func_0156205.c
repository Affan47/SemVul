unsigned int dccp_sync_mss(struct sock *sk, u32 pmtu)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct dccp_sock *dp = dccp_sk(sk);
	int mss_now = (pmtu - icsk->icsk_af_ops->net_header_len -
		       sizeof(struct dccp_hdr) - sizeof(struct dccp_hdr_ext));


	mss_now -= icsk->icsk_ext_hdr_len;


	mss_now -= ((5 + 6 + 10 + 6 + 6 + 6 + 3) / 4) * 4;


	icsk->icsk_pmtu_cookie = pmtu;
	dp->dccps_mss_cache = mss_now;

	return mss_now;
}
