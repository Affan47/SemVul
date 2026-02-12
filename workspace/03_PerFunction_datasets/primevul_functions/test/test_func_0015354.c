static void io_req_complete_fail_submit(struct io_kiocb *req)
{


	req->flags &= ~REQ_F_HARDLINK;
	req->flags |= REQ_F_LINK;
	io_req_complete_failed(req, req->result);
}
