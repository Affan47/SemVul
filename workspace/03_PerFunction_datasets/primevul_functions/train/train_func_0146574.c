static void dccp_finish_passive_close(struct sock *sk)
{
	switch (sk->sk_state) {
	case DCCP_PASSIVE_CLOSE:

		dccp_send_reset(sk, DCCP_RESET_CODE_CLOSED);
		dccp_set_state(sk, DCCP_CLOSED);
		break;
	case DCCP_PASSIVE_CLOSEREQ:


		dccp_send_close(sk, 1);
		dccp_set_state(sk, DCCP_CLOSING);
	}
}
