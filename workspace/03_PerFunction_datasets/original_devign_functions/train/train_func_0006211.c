static void vhost_virtqueue_stop(struct vhost_dev *dev, struct VirtIODevice *vdev, struct vhost_virtqueue *vq,
                                 unsigned idx) {
    int vhost_vq_index             = dev->vhost_ops->vhost_get_vq_index(dev, idx);
    struct vhost_vring_state state = {
        .index = vhost_vq_index,
    };
    int r;
    r = dev->vhost_ops->vhost_get_vring_base(dev, &state);
    if (r < 0) {
        VHOST_OPS_DEBUG("vhost VQ %d ring restore failed: %d", idx, r);
    } else {
        virtio_queue_set_last_avail_idx(vdev, idx, state.num);
    }
    virtio_queue_invalidate_signalled_used(vdev, idx);
    virtio_queue_update_used_idx(vdev, idx);
