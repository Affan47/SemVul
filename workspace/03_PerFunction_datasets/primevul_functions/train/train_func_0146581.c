static inline int dccp_listen_start(struct sock *sk, int backlog)
{
	struct dccp_sock *dp = dccp_sk(sk);

	dp->dccps_role = DCCP_ROLE_LISTEN;

	if (dccp_feat_finalise_settings(dp))
		return -EPROTO;
	return inet_csk_listen_start(sk, backlog);
}
