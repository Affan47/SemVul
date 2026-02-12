static int io_read(struct io_kiocb *req, unsigned int issue_flags)
{
	struct io_rw_state __s, *s = &__s;
	struct iovec *iovec;
	struct kiocb *kiocb = &req->rw.kiocb;
	bool force_nonblock = issue_flags & IO_URING_F_NONBLOCK;
	struct io_async_rw *rw;
	ssize_t ret, ret2;
	loff_t *ppos;

	if (!req_has_async_data(req)) {
		ret = io_import_iovec(READ, req, &iovec, s, issue_flags);
		if (unlikely(ret < 0))
			return ret;
	} else {


		if (req->flags & REQ_F_BUFFER_SELECT) {
			ret = io_import_iovec(READ, req, &iovec, s, issue_flags);
			if (unlikely(ret < 0))
				return ret;
		}

		rw = req->async_data;
		s = &rw->s;


		iov_iter_restore(&s->iter, &s->iter_state);
		iovec = NULL;
	}
	ret = io_rw_init_file(req, FMODE_READ);
	if (unlikely(ret)) {
		kfree(iovec);
		return ret;
	}
	req->result = iov_iter_count(&s->iter);

	if (force_nonblock) {

		if (unlikely(!io_file_supports_nowait(req))) {
			ret = io_setup_async_rw(req, iovec, s, true);
			return ret ?: -EAGAIN;
		}
		kiocb->ki_flags |= IOCB_NOWAIT;
	} else {

		kiocb->ki_flags &= ~IOCB_NOWAIT;
	}

	ppos = io_kiocb_update_pos(req);

	ret = rw_verify_area(READ, req->file, ppos, req->result);
	if (unlikely(ret)) {
		kfree(iovec);
		return ret;
	}

	ret = io_iter_do_read(req, &s->iter);

	if (ret == -EAGAIN || (req->flags & REQ_F_REISSUE)) {
		req->flags &= ~REQ_F_REISSUE;

		if (req->opcode == IORING_OP_READ && file_can_poll(req->file))
			return -EAGAIN;

		if (!force_nonblock && !(req->ctx->flags & IORING_SETUP_IOPOLL))
			goto done;

		if (req->flags & REQ_F_NOWAIT)
			goto done;
		ret = 0;
	} else if (ret == -EIOCBQUEUED) {
		goto out_free;
	} else if (ret == req->result || ret <= 0 || !force_nonblock ||
		   (req->flags & REQ_F_NOWAIT) || !need_read_all(req)) {

		goto done;
	}


	iov_iter_restore(&s->iter, &s->iter_state);

	ret2 = io_setup_async_rw(req, iovec, s, true);
	if (ret2)
		return ret2;

	iovec = NULL;
	rw = req->async_data;
	s = &rw->s;


	do {


		iov_iter_advance(&s->iter, ret);
		if (!iov_iter_count(&s->iter))
			break;
		rw->bytes_done += ret;
		iov_iter_save_state(&s->iter, &s->iter_state);


		if (!io_rw_should_retry(req)) {
			kiocb->ki_flags &= ~IOCB_WAITQ;
			return -EAGAIN;
		}


		ret = io_iter_do_read(req, &s->iter);
		if (ret == -EIOCBQUEUED)
			return 0;

		kiocb->ki_flags &= ~IOCB_WAITQ;
		iov_iter_restore(&s->iter, &s->iter_state);
	} while (ret > 0);
done:
	kiocb_done(req, ret, issue_flags);
out_free:

	if (iovec)
		kfree(iovec);
	return 0;
}
