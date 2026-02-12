static int tipc_wait_for_accept(struct socket *sock, long timeo)
{
	struct sock *sk = sock->sk;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int err;


	for (;;) {
		if (timeo && skb_queue_empty(&sk->sk_receive_queue)) {
			add_wait_queue(sk_sleep(sk), &wait);
			release_sock(sk);
			timeo = wait_woken(&wait, TASK_INTERRUPTIBLE, timeo);
			lock_sock(sk);
			remove_wait_queue(sk_sleep(sk), &wait);
		}
		err = 0;
		if (!skb_queue_empty(&sk->sk_receive_queue))
			break;
		err = -EAGAIN;
		if (!timeo)
			break;
		err = sock_intr_errno(timeo);
		if (signal_pending(current))
			break;
	}
	return err;
}
