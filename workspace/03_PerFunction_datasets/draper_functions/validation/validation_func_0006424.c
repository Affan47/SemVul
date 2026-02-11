usbtv_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct usbtv *usbtv = vb2_get_drv_priv(vb->vb2_queue);
	struct usbtv_buf *buf = container_of(vbuf, struct usbtv_buf, vb);
	unsigned long flags;

	if (usbtv->udev == NULL) {
		vb2_buffer_done(vb, VB2_BUF_STATE_ERROR);
		return;
	}

	spin_lock_irqsave(&usbtv->buflock, flags);
	list_add_tail(&buf->list, &usbtv->bufs);
	spin_unlock_irqrestore(&usbtv->buflock, flags);
}
