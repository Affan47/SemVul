static void __io_poll_execute(struct io_kiocb *req, int mask, int events)
{
	req->result = mask;


	req->apoll_events = events;
	if (req->opcode == IORING_OP_POLL_ADD)
		req->io_task_work.func = io_poll_task_func;
	else
		req->io_task_work.func = io_apoll_task_func;

	trace_io_uring_task_add(req->ctx, req, req->user_data, req->opcode, mask);
	io_req_task_work_add(req, false);
}
