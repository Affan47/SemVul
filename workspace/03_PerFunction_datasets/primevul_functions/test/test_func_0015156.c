static void io_poll_cancel_req(struct io_kiocb *req)
{
	io_poll_mark_cancelled(req);

	io_poll_execute(req, 0, 0);
}
