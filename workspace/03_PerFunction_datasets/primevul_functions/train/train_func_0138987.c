static void hidp_idle_timeout(struct timer_list *t)
{
	struct hidp_session *session = from_timer(session, t, timer);


	session->intr_sock->sk->sk_err = EUNATCH;
	session->ctrl_sock->sk->sk_err = EUNATCH;
	wake_up_interruptible(sk_sleep(session->intr_sock->sk));
	wake_up_interruptible(sk_sleep(session->ctrl_sock->sk));

	hidp_session_terminate(session);
}
