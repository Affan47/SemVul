saa7164_encoder_stop_streaming(struct saa7164_port *port)
{
	struct saa7164_dev *dev = port->dev;
	struct saa7164_buffer *buf;
	struct saa7164_user_buffer *ubuf;
	struct list_head *c, *n;
	int ret;

	dprintk(DBGLVL_ENC, "%s(port=%d)\n", __func__, port->nr);

	ret = saa7164_encoder_pause_port(port);
	ret = saa7164_encoder_acquire_port(port);
	ret = saa7164_encoder_stop_port(port);

	dprintk(DBGLVL_ENC, "%s(port=%d) Hardware stopped\n", __func__,
		port->nr);


	mutex_lock(&port->dmaqueue_lock);


	list_for_each_safe(c, n, &port->dmaqueue.list) {
		buf = list_entry(c, struct saa7164_buffer, list);
		buf->flags = SAA7164_BUFFER_FREE;
		buf->pos = 0;
	}

	list_for_each_safe(c, n, &port->list_buf_used.list) {
		ubuf = list_entry(c, struct saa7164_user_buffer, list);
		ubuf->pos = 0;
		list_move_tail(&ubuf->list, &port->list_buf_free.list);
	}

	mutex_unlock(&port->dmaqueue_lock);


	saa7164_encoder_buffers_dealloc(port);

	dprintk(DBGLVL_ENC, "%s(port=%d) Released\n", __func__, port->nr);

	return ret;
}
