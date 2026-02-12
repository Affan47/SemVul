static void tipc_sk_retry_connect(struct sock *sk, struct sk_buff_head *list)
{
	struct tipc_sock *tsk = tipc_sk(sk);


	if (tsk->cong_link_cnt) {
		sk_reset_timer(sk, &sk->sk_timer, msecs_to_jiffies(100));
		return;
	}

	tipc_msg_skb_clone(&sk->sk_write_queue, list);
}
