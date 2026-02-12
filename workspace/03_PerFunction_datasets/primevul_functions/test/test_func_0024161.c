static void virtio_net_vnet_endian_status(VirtIONet *n, uint8_t status)
{
    VirtIODevice *vdev = VIRTIO_DEVICE(n);
    int queues = n->multiqueue ? n->max_queues : 1;

    if (virtio_net_started(n, status)) {


        n->needs_vnet_hdr_swap = virtio_net_set_vnet_endian(vdev, n->nic->ncs,
                                                            queues, true);
    } else if (virtio_net_started(n, vdev->status)) {


        virtio_net_set_vnet_endian(vdev, n->nic->ncs, queues, false);
    }
}
