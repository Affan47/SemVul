static int econet_release(struct socket *sock)
{
	struct sock *sk;

	mutex_lock(&econet_mutex);

	sk = sock->sk;
	if (!sk)
		goto out_unlock;

	econet_remove_socket(&econet_sklist, sk);


	sk->sk_state_change(sk);

	sock_orphan(sk);


	skb_queue_purge(&sk->sk_receive_queue);

	if (sk_has_allocations(sk)) {
		sk->sk_timer.data     = (unsigned long)sk;
		sk->sk_timer.expires  = jiffies + HZ;
		sk->sk_timer.function = econet_destroy_timer;
		add_timer(&sk->sk_timer);

		goto out_unlock;
	}

	sk_free(sk);

out_unlock:
	mutex_unlock(&econet_mutex);
	return 0;
}
