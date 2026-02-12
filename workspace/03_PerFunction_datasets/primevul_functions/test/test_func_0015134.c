static int io_sync_file_range(struct io_kiocb *req, unsigned int issue_flags)
{
	int ret;


	if (issue_flags & IO_URING_F_NONBLOCK)
		return -EAGAIN;

	ret = sync_file_range(req->file, req->sync.off, req->sync.len,
				req->sync.flags);
	if (ret < 0)
		req_set_fail(req);
	io_req_complete(req, ret);
	return 0;
}
