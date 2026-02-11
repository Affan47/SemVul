e2_ext_read(struct Epson_Scanner *s)
{
	SANE_Status status = SANE_STATUS_GOOD;
	ssize_t buf_len = 0, read;


	if (s->ptr == s->end) {

		if (s->eof)
			return SANE_STATUS_EOF;

		s->ext_counter++;


		buf_len = s->ext_block_len;

		if (s->ext_counter == s->ext_blocks && s->ext_last_len)
			buf_len = s->ext_last_len;

		DBG(18, "%s: block %d/%d, size %lu\n", __func__,
			s->ext_counter, s->ext_blocks,
			(unsigned long) buf_len);


		read = e2_recv(s, s->buf, buf_len + 1, &status);

		DBG(18, "%s: read %lu bytes\n", __func__, (unsigned long) read);

		if (read != buf_len + 1)
			return SANE_STATUS_IO_ERROR;

		if (s->buf[buf_len] & FSG_STATUS_CANCEL_REQ) {
			DBG(0, "%s: cancel request received\n", __func__);
			e2_cancel(s);
			return SANE_STATUS_CANCELLED;
		}

		if (s->buf[buf_len] & (FSG_STATUS_FER | FSG_STATUS_NOT_READY))
			return SANE_STATUS_IO_ERROR;


		if (s->ext_counter < s->ext_blocks) {
			size_t next_len = s->ext_block_len;

			if (s->ext_counter == (s->ext_blocks - 1))
				next_len = s->ext_last_len;

			if (s->canceling) {
				e2_cancel(s);
				return SANE_STATUS_CANCELLED;
			}

			status = e2_ack_next(s, next_len + 1);
		} else
			s->eof = SANE_TRUE;

		s->end = s->buf + buf_len;
		s->ptr = s->buf;
	}

	return status;
}
