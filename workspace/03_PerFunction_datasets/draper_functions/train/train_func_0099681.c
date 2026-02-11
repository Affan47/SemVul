iax_handle_txreject(struct iax_session *s)
{
	struct iax_session *s0, *s1;

	s0 = s;
	s1 = iax_find_session2(s0->transferpeer);
	if (s1 != NULL &&
		 s0->transferpeer == s1->callno &&
		 s1->transferring) {
		if (s1->transfer_moh) {
			s1->transfer_moh = 0;
			send_command_immediate(s1, AST_FRAME_IAX, IAX_COMMAND_UNQUELCH, 0, NULL, 0, s1->iseqno);
		}
	}
	if (s0->transfer_moh) {
		s0->transfer_moh = 0;
		send_command_immediate(s0, AST_FRAME_IAX, IAX_COMMAND_UNQUELCH, 0, NULL, 0, s0->iseqno);
	}

	memset(&s->transfer, 0, sizeof(s->transfer));
	s->transferring = TRANSFER_NONE;
	s->transferpeer = 0;
	s->transfer_moh = 0;
}
