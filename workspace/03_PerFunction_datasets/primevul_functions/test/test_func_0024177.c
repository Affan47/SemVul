static int virtio_net_max_tx_queue_size(VirtIONet *n)
{
    NetClientState *peer = n->nic_conf.peers.ncs[0];


    if (!peer) {
        return VIRTIO_NET_TX_QUEUE_DEFAULT_SIZE;
    }

    if (peer->info->type != NET_CLIENT_DRIVER_VHOST_USER) {
        return VIRTIO_NET_TX_QUEUE_DEFAULT_SIZE;
    }

    return VIRTQUEUE_MAX_SIZE;
}
