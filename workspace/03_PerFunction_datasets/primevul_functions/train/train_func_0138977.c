static int hidp_session_thread(void *arg)
{
	struct hidp_session *session = arg;
	DEFINE_WAIT_FUNC(ctrl_wait, hidp_session_wake_function);
	DEFINE_WAIT_FUNC(intr_wait, hidp_session_wake_function);

	BT_DBG("session %p", session);


	hidp_session_get(session);
	__module_get(THIS_MODULE);
	set_user_nice(current, -15);
	hidp_set_timer(session);

	add_wait_queue(sk_sleep(session->ctrl_sock->sk), &ctrl_wait);
	add_wait_queue(sk_sleep(session->intr_sock->sk), &intr_wait);


	smp_mb();


	atomic_inc(&session->state);
	wake_up(&session->state_queue);


	hidp_session_run(session);


	remove_wait_queue(sk_sleep(session->intr_sock->sk), &intr_wait);
	remove_wait_queue(sk_sleep(session->intr_sock->sk), &ctrl_wait);
	wake_up_interruptible(&session->report_queue);
	hidp_del_timer(session);


	l2cap_unregister_user(session->conn, &session->user);
	hidp_session_put(session);

	module_put_and_exit(0);
	return 0;
}
