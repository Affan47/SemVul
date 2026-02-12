static int rpmsg_recv_single(struct virtproc_info *vrp, struct device *dev,
			     struct rpmsg_hdr *msg, unsigned int len)
{
	struct rpmsg_endpoint *ept;
	struct scatterlist sg;
	bool little_endian = virtio_is_little_endian(vrp->vdev);
	unsigned int msg_len = __rpmsg16_to_cpu(little_endian, msg->len);
	int err;

	dev_dbg(dev, "From: 0x%x, To: 0x%x, Len: %d, Flags: %d, Reserved: %d\n",
		__rpmsg32_to_cpu(little_endian, msg->src),
		__rpmsg32_to_cpu(little_endian, msg->dst), msg_len,
		__rpmsg16_to_cpu(little_endian, msg->flags),
		__rpmsg32_to_cpu(little_endian, msg->reserved));
#if defined(CONFIG_DYNAMIC_DEBUG)
	dynamic_hex_dump("rpmsg_virtio RX: ", DUMP_PREFIX_NONE, 16, 1,
			 msg, sizeof(*msg) + msg_len, true);
#endif


	if (len > vrp->buf_size ||
	    msg_len > (len - sizeof(struct rpmsg_hdr))) {
		dev_warn(dev, "inbound msg too big: (%d, %d)\n", len, msg_len);
		return -EINVAL;
	}


	mutex_lock(&vrp->endpoints_lock);

	ept = idr_find(&vrp->endpoints, __rpmsg32_to_cpu(little_endian, msg->dst));


	if (ept)
		kref_get(&ept->refcount);

	mutex_unlock(&vrp->endpoints_lock);

	if (ept) {

		mutex_lock(&ept->cb_lock);

		if (ept->cb)
			ept->cb(ept->rpdev, msg->data, msg_len, ept->priv,
				__rpmsg32_to_cpu(little_endian, msg->src));

		mutex_unlock(&ept->cb_lock);


		kref_put(&ept->refcount, __ept_release);
	} else
		dev_warn_ratelimited(dev, "msg received with no recipient\n");


	rpmsg_sg_init(&sg, msg, vrp->buf_size);


	err = virtqueue_add_inbuf(vrp->rvq, &sg, 1, msg, GFP_KERNEL);
	if (err < 0) {
		dev_err(dev, "failed to add a virtqueue buffer: %d\n", err);
		return err;
	}

	return 0;
}
