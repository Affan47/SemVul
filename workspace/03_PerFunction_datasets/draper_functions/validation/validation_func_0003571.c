uvc_buffer_finish(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct uvc_video_queue *queue = vb2_get_drv_priv(vb->vb2_queue);
	struct uvc_streaming *stream = uvc_queue_to_stream(queue);
	struct uvc_buffer *buf = container_of(vbuf, struct uvc_buffer, buf);

	if (vb->state == VB2_BUF_STATE_DONE)
		uvc_video_clock_update(stream, vbuf, buf);
}
