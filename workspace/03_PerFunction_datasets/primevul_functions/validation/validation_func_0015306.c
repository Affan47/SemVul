flush_shadow_used_ring_split(struct virtio_net *dev, struct vhost_virtqueue *vq)
{
	uint16_t used_idx = vq->last_used_idx & (vq->size - 1);

	if (used_idx + vq->shadow_used_idx <= vq->size) {
		do_flush_shadow_used_ring_split(dev, vq, used_idx, 0,
					  vq->shadow_used_idx);
	} else {
		uint16_t size;


		size = vq->size - used_idx;
		do_flush_shadow_used_ring_split(dev, vq, used_idx, 0, size);


		do_flush_shadow_used_ring_split(dev, vq, 0, size,
					  vq->shadow_used_idx - size);
	}
	vq->last_used_idx += vq->shadow_used_idx;

	vhost_log_cache_sync(dev, vq);

	__atomic_add_fetch(&vq->used->idx, vq->shadow_used_idx,
			   __ATOMIC_RELEASE);
	vq->shadow_used_idx = 0;
	vhost_log_used_vring(dev, vq, offsetof(struct vring_used, idx),
		sizeof(vq->used->idx));
}
