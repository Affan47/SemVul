void qemu_flush_or_purge_queued_packets(NetClientState *nc, bool purge)
{
    nc->receive_disabled = 0;

    if (nc->peer && nc->peer->info->type == NET_CLIENT_DRIVER_HUBPORT) {
        if (net_hub_flush(nc->peer)) {
            qemu_notify_event();
        }
    }
    if (qemu_net_queue_flush(nc->incoming_queue)) {


        qemu_notify_event();
    } else if (purge) {

        qemu_net_queue_purge(nc->incoming_queue, nc->peer);
    }
}
