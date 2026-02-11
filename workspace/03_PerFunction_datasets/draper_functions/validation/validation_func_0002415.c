tb_ctl_rx_callback(struct tb_ring *ring, struct ring_frame *frame,
			       bool canceled)
{
	struct ctl_pkg *pkg = container_of(frame, typeof(*pkg), frame);

	if (canceled)
		return;


	if (frame->size < 4 || frame->size % 4 != 0) {
		tb_ctl_err(pkg->ctl, "RX: invalid size %#x, dropping packet\n",
			   frame->size);
		goto rx;
	}

	frame->size -= 4;
	if (*(__be32 *) (pkg->buffer + frame->size)
			!= tb_crc(pkg->buffer, frame->size)) {
		tb_ctl_err(pkg->ctl,
			   "RX: checksum mismatch, dropping packet\n");
		goto rx;
	}
	be32_to_cpu_array(pkg->buffer, pkg->buffer, frame->size / 4);

	if (frame->eof == TB_CFG_PKG_EVENT) {
		tb_ctl_handle_plug_event(pkg->ctl, pkg);
		goto rx;
	}
	if (!kfifo_put(&pkg->ctl->response_fifo, pkg)) {
		tb_ctl_err(pkg->ctl, "RX: fifo is full\n");
		goto rx;
	}
	complete(&pkg->ctl->response_ready);
	return;
rx:
	tb_ctl_rx_submit(pkg);
}
