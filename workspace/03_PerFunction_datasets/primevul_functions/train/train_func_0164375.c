void dccp_close(struct sock *sk, long timeout)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct sk_buff *skb;
	int state;

	lock_sock(sk);

	sk->sk_shutdown = SHUTDOWN_MASK;

	if (sk->sk_state == DCCP_LISTEN) {
		dccp_set_state(sk, DCCP_CLOSED);


		inet_csk_listen_stop(sk);

		goto adjudge_to_death;
	}

	sk_stop_timer(sk, &dp->dccps_xmit_timer);


	while ((skb = __skb_dequeue(&sk->sk_receive_queue)) != NULL) {
		__kfree_skb(skb);
	}

	if (sock_flag(sk, SOCK_LINGER) && !sk->sk_lingertime) {

		sk->sk_prot->disconnect(sk, 0);
	} else if (dccp_close_state(sk)) {
		dccp_send_close(sk, 1);
	}

	sk_stream_wait_close(sk, timeout);

adjudge_to_death:
	state = sk->sk_state;
	sock_hold(sk);
	sock_orphan(sk);
	atomic_inc(sk->sk_prot->orphan_count);


	release_sock(sk);


	local_bh_disable();
	bh_lock_sock(sk);
	BUG_TRAP(!sock_owned_by_user(sk));


	if (state != DCCP_CLOSED && sk->sk_state == DCCP_CLOSED)
		goto out;


	if (sk->sk_state == DCCP_CLOSING) {


		inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
					  inet_csk(sk)->icsk_rto,
					  DCCP_RTO_MAX);
#if 0

		dccp_set_state(sk, DCCP_CLOSED);
#endif
	}

	if (sk->sk_state == DCCP_CLOSED)
		inet_csk_destroy_sock(sk);


out:
	bh_unlock_sock(sk);
	local_bh_enable();
	sock_put(sk);
}
