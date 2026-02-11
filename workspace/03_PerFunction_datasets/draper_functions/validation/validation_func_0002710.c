cx25840_ir_rx_read(struct v4l2_subdev *sd, u8 *buf, size_t count,
			      ssize_t *num)
{
	struct cx25840_ir_state *ir_state = to_ir_state(sd);
	bool invert;
	u16 divider;
	unsigned int i, n;
	union cx25840_ir_fifo_rec *p;
	unsigned u, v, w;

	if (ir_state == NULL)
		return -ENODEV;

	invert = (bool) atomic_read(&ir_state->rx_invert);
	divider = (u16) atomic_read(&ir_state->rxclk_divider);

	n = count / sizeof(union cx25840_ir_fifo_rec)
		* sizeof(union cx25840_ir_fifo_rec);
	if (n == 0) {
		*num = 0;
		return 0;
	}

	n = kfifo_out_locked(&ir_state->rx_kfifo, buf, n,
			     &ir_state->rx_kfifo_lock);

	n /= sizeof(union cx25840_ir_fifo_rec);
	*num = n * sizeof(union cx25840_ir_fifo_rec);

	for (p = (union cx25840_ir_fifo_rec *) buf, i = 0; i < n; p++, i++) {

		if ((p->hw_fifo_data & FIFO_RXTX_RTO) == FIFO_RXTX_RTO) {

			u = 0;
			w = 1;
		} else {
			u = (p->hw_fifo_data & FIFO_RXTX_LVL) ? 1 : 0;
			if (invert)
				u = u ? 0 : 1;
			w = 0;
		}

		v = (unsigned) pulse_width_count_to_ns(
				  (u16) (p->hw_fifo_data & FIFO_RXTX), divider);
		if (v > IR_MAX_DURATION)
			v = IR_MAX_DURATION;

		init_ir_raw_event(&p->ir_core_data);
		p->ir_core_data.pulse = u;
		p->ir_core_data.duration = v;
		p->ir_core_data.timeout = w;

		v4l2_dbg(2, ir_debug, sd, "rx read: %10u ns  %s  %s\n",
			 v, u ? "mark" : "space", w ? "(timed out)" : "");
		if (w)
			v4l2_dbg(2, ir_debug, sd, "rx read: end of rx\n");
	}
	return 0;
}
