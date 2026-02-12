static void net_vm_change_state_handler(void *opaque, bool running,
                                        RunState state)
{
    NetClientState *nc;
    NetClientState *tmp;

    QTAILQ_FOREACH_SAFE(nc, &net_clients, next, tmp) {
        if (running) {

            if (nc->peer && qemu_can_send_packet(nc)) {
                qemu_flush_queued_packets(nc->peer);
            }
        } else {


            qemu_flush_or_purge_queued_packets(nc, true);
        }
    }
}
