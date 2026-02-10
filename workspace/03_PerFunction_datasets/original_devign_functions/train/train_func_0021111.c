static void virtio_blk_rw_complete(void *opaque, int ret) {
    VirtIOBlockReq *next = opaque;
    while (next) {
        VirtIOBlockReq *req = next;
        next                = req->mr_next;
        trace_virtio_blk_rw_complete(req, ret);
        if (req->qiov.nalloc != -1) {
            qemu_iovec_destroy(&req->qiov);
        }
        if (ret) {
            int p        = virtio_ldl_p(VIRTIO_DEVICE(req->dev), &req->out.type);
            bool is_read = !(p & VIRTIO_BLK_T_OUT);
