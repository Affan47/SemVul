void qemu_del_nic(NICState *nic)
{
    int i, queues = MAX(nic->conf->peers.queues, 1);

    qemu_macaddr_set_free(&nic->conf->macaddr);

    for (i = 0; i < queues; i++) {
        NetClientState *nc = qemu_get_subqueue(nic, i);

        if (nic->peer_deleted) {
            qemu_free_net_client(nc->peer);
        } else if (nc->peer) {

            qemu_purge_queued_packets(nc->peer);
        }
    }

    for (i = queues - 1; i >= 0; i--) {
        NetClientState *nc = qemu_get_subqueue(nic, i);

        qemu_cleanup_net_client(nc);
        qemu_free_net_client(nc);
    }

    g_free(nic);
}
