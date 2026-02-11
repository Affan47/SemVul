virtio_gpu_queue_ctrl_buffer_locked(struct virtio_gpu_device *vgdev,
					       struct virtio_gpu_vbuffer *vbuf)
{
	struct virtqueue *vq = vgdev->ctrlq.vq;
	struct scatterlist *sgs[3], vcmd, vout, vresp;
	int outcnt = 0, incnt = 0;
	int ret;

	if (!vgdev->vqs_ready)
		return -ENODEV;

	sg_init_one(&vcmd, vbuf->buf, vbuf->size);
	sgs[outcnt+incnt] = &vcmd;
	outcnt++;

	if (vbuf->data_size) {
		sg_init_one(&vout, vbuf->data_buf, vbuf->data_size);
		sgs[outcnt + incnt] = &vout;
		outcnt++;
	}

	if (vbuf->resp_size) {
		sg_init_one(&vresp, vbuf->resp_buf, vbuf->resp_size);
		sgs[outcnt + incnt] = &vresp;
		incnt++;
	}

retry:
	ret = virtqueue_add_sgs(vq, sgs, outcnt, incnt, vbuf, GFP_ATOMIC);
	if (ret == -ENOSPC) {
		spin_unlock(&vgdev->ctrlq.qlock);
		wait_event(vgdev->ctrlq.ack_queue, vq->num_free);
		spin_lock(&vgdev->ctrlq.qlock);
		goto retry;
	} else {
		virtqueue_kick(vq);
	}

	if (!ret)
		ret = vq->num_free;
	return ret;
}
