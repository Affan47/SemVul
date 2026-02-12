static int tcp_orphan_retries(struct sock *sk, bool alive)
{
	int retries = sock_net(sk)->ipv4.sysctl_tcp_orphan_retries;


	if (sk->sk_err_soft && !alive)
		retries = 0;


	if (retries == 0 && alive)
		retries = 8;
	return retries;
}
