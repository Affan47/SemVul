static int sctp_setsockopt_partial_delivery_point(struct sock *sk, u32 *val,
						  unsigned int optlen)
{
	if (optlen != sizeof(u32))
		return -EINVAL;


	if (*val > (sk->sk_rcvbuf >> 1))
		return -EINVAL;

	sctp_sk(sk)->pd_point = *val;

	return 0;
}
