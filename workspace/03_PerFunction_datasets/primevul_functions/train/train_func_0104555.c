do_sync_target_write(MirrorBlockJob *job, MirrorMethod method,
                     uint64_t offset, uint64_t bytes,
                     QEMUIOVector *qiov, int flags)
{
    int ret;
    size_t qiov_offset = 0;
    int64_t bitmap_offset, bitmap_end;

    if (!QEMU_IS_ALIGNED(offset, job->granularity) &&
        bdrv_dirty_bitmap_get(job->dirty_bitmap, offset))
    {


            qiov_offset = QEMU_ALIGN_UP(offset, job->granularity) - offset;
            if (bytes <= qiov_offset) {

                return;
            }
            offset += qiov_offset;
            bytes -= qiov_offset;
    }

    if (!QEMU_IS_ALIGNED(offset + bytes, job->granularity) &&
        bdrv_dirty_bitmap_get(job->dirty_bitmap, offset + bytes - 1))
    {
        uint64_t tail = (offset + bytes) % job->granularity;

        if (bytes <= tail) {

            return;
        }
        bytes -= tail;
    }


    bitmap_offset = QEMU_ALIGN_UP(offset, job->granularity);
    bitmap_end = QEMU_ALIGN_DOWN(offset + bytes, job->granularity);
    if (bitmap_offset < bitmap_end) {
        bdrv_reset_dirty_bitmap(job->dirty_bitmap, bitmap_offset,
                                bitmap_end - bitmap_offset);
    }

    job_progress_increase_remaining(&job->common.job, bytes);

    switch (method) {
    case MIRROR_METHOD_COPY:
        ret = blk_co_pwritev_part(job->target, offset, bytes,
                                  qiov, qiov_offset, flags);
        break;

    case MIRROR_METHOD_ZERO:
        assert(!qiov);
        ret = blk_co_pwrite_zeroes(job->target, offset, bytes, flags);
        break;

    case MIRROR_METHOD_DISCARD:
        assert(!qiov);
        ret = blk_co_pdiscard(job->target, offset, bytes);
        break;

    default:
        abort();
    }

    if (ret >= 0) {
        job_progress_update(&job->common.job, bytes);
    } else {
        BlockErrorAction action;


        bitmap_offset = QEMU_ALIGN_DOWN(offset, job->granularity);
        bitmap_end = QEMU_ALIGN_UP(offset + bytes, job->granularity);
        bdrv_set_dirty_bitmap(job->dirty_bitmap, bitmap_offset,
                              bitmap_end - bitmap_offset);
        job->actively_synced = false;

        action = mirror_error_action(job, false, -ret);
        if (action == BLOCK_ERROR_ACTION_REPORT) {
            if (!job->ret) {
                job->ret = ret;
            }
        }
    }
}
