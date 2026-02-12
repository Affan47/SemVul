static bool io_resubmit_prep(struct io_kiocb *req)
{
	struct io_async_rw *rw = req->async_data;

	if (!rw)
		return !io_req_prep_async(req);

	iov_iter_revert(&rw->iter, req->result - iov_iter_count(&rw->iter));
	return true;
}
