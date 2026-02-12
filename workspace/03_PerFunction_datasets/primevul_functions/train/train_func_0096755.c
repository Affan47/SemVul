static void virtio_net_vnet_endian_status(VirtIONet *n, uint8_t status)
{
    VirtIODevice *vdev = VIRTIO_DEVICE(n);
    int queue_pairs = n->multiqueue ? n->max_queue_pairs : 1;

    if (virtio_net_started(n, status)) {


        n->needs_vnet_hdr_swap = virtio_net_set_vnet_endian(vdev, n->nic->ncs,
                                                            queue_pairs, true);
    } else if (virtio_net_started(n, vdev->status)) {


        virtio_net_set_vnet_endian(vdev, n->nic->ncs, queue_pairs, false);
    }
}
