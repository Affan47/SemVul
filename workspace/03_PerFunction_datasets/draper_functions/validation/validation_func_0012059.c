imap_finish(struct mailbox *mp)
{
	while (mp->mb_sock.s_fd > 0 && mp->mb_active & MB_COMD)
		imap_answer(mp, 1);
	return OKAY;
}
