static int virtio_net_post_load_device(void *opaque, int version_id)
{
    VirtIONet *n = opaque;
    VirtIODevice *vdev = VIRTIO_DEVICE(n);
    int i, link_down;

    trace_virtio_net_post_load_device();
    virtio_net_set_mrg_rx_bufs(n, n->mergeable_rx_bufs,
                               virtio_vdev_has_feature(vdev,
                                                       VIRTIO_F_VERSION_1),
                               virtio_vdev_has_feature(vdev,
                                                       VIRTIO_NET_F_HASH_REPORT));


    if (n->mac_table.in_use > MAC_TABLE_ENTRIES) {
        n->mac_table.in_use = 0;
    }

    if (!virtio_vdev_has_feature(vdev, VIRTIO_NET_F_CTRL_GUEST_OFFLOADS)) {
        n->curr_guest_offloads = virtio_net_supported_guest_offloads(n);
    }


    n->saved_guest_offloads = n->curr_guest_offloads;

    virtio_net_set_queues(n);


    for (i = 0; i < n->mac_table.in_use; i++) {
        if (n->mac_table.macs[i * ETH_ALEN] & 1) {
            break;
        }
    }
    n->mac_table.first_multi = i;


    link_down = (n->status & VIRTIO_NET_S_LINK_UP) == 0;
    for (i = 0; i < n->max_queues; i++) {
        qemu_get_subqueue(n->nic, i)->link_down = link_down;
    }

    if (virtio_vdev_has_feature(vdev, VIRTIO_NET_F_GUEST_ANNOUNCE) &&
        virtio_vdev_has_feature(vdev, VIRTIO_NET_F_CTRL_VQ)) {
        qemu_announce_timer_reset(&n->announce_timer, migrate_announce_params(),
                                  QEMU_CLOCK_VIRTUAL,
                                  virtio_net_announce_timer, n);
        if (n->announce_timer.round) {
            timer_mod(n->announce_timer.tm,
                      qemu_clock_get_ms(n->announce_timer.type));
        } else {
            qemu_announce_timer_del(&n->announce_timer, false);
        }
    }

    if (n->rss_data.enabled) {
        n->rss_data.enabled_software_rss = n->rss_data.populate_hash;
        if (!n->rss_data.populate_hash) {
            if (!virtio_net_attach_epbf_rss(n)) {
                if (get_vhost_net(qemu_get_queue(n->nic)->peer)) {
                    warn_report("Can't post-load eBPF RSS for vhost");
                } else {
                    warn_report("Can't post-load eBPF RSS - "
                                "fallback to software RSS");
                    n->rss_data.enabled_software_rss = true;
                }
            }
        }

        trace_virtio_net_rss_enable(n->rss_data.hash_types,
                                    n->rss_data.indirections_len,
                                    sizeof(n->rss_data.key));
    } else {
        trace_virtio_net_rss_disable();
    }
    return 0;
}
