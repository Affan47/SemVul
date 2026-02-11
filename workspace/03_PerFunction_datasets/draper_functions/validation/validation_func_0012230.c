r5l_stripe_write_finished(struct stripe_head *sh)
{
	struct r5l_io_unit *io;

	io = sh->log_io;
	sh->log_io = NULL;

	if (io && atomic_dec_and_test(&io->pending_stripe))
		__r5l_stripe_write_finished(io);
}
