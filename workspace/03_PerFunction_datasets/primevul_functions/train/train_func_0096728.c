static int virtio_net_post_load_virtio(VirtIODevice *vdev)
{
    VirtIONet *n = VIRTIO_NET(vdev);


    n->curr_guest_offloads = n->saved_guest_offloads;
    if (peer_has_vnet_hdr(n)) {
        virtio_net_apply_guest_offloads(n);
    }

    return 0;
}
