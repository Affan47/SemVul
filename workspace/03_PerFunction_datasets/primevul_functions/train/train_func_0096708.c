static void virtio_net_change_num_queue_pairs(VirtIONet *n, int new_max_queue_pairs)
{
    VirtIODevice *vdev = VIRTIO_DEVICE(n);
    int old_num_queues = virtio_get_num_queues(vdev);
    int new_num_queues = new_max_queue_pairs * 2 + 1;
    int i;

    assert(old_num_queues >= 3);
    assert(old_num_queues % 2 == 1);

    if (old_num_queues == new_num_queues) {
        return;
    }


    virtio_del_queue(vdev, old_num_queues - 1);

    for (i = new_num_queues - 1; i < old_num_queues - 1; i += 2) {

        virtio_net_del_queue(n, i / 2);
    }

    for (i = old_num_queues - 1; i < new_num_queues - 1; i += 2) {

        virtio_net_add_queue(n, i / 2);
    }


    n->ctrl_vq = virtio_add_queue(vdev, 64, virtio_net_handle_ctrl);
}
