dht_write_with_holes (xlator_t *to, fd_t *fd, struct iovec *vec, int count,
                      int32_t size, off_t offset, struct iobref *iobref)
{
        int i            = 0;
        int ret          = -1;
        int start_idx    = 0;
        int tmp_offset   = 0;
        int write_needed = 0;
        int buf_len      = 0;
        int size_pending = 0;
        char *buf        = NULL;


        for (i = 0; i < count; i++) {
                buf = vec[i].iov_base;
                buf_len = vec[i].iov_len;

                for (start_idx = 0; (start_idx + GF_DISK_SECTOR_SIZE) <= buf_len;
                     start_idx += GF_DISK_SECTOR_SIZE) {

                        if (mem_0filled (buf + start_idx, GF_DISK_SECTOR_SIZE) != 0) {
                                write_needed = 1;
                                continue;
                        }

                        if (write_needed) {
                                ret = syncop_write (to, fd, (buf + tmp_offset),
                                                    (start_idx - tmp_offset),
                                                    (offset + tmp_offset),
                                                    iobref);

                                if (ret < 0) {
                                        gf_log (THIS->name, GF_LOG_WARNING,
                                                "failed to write (%s)",
                                                strerror (errno));
                                        goto out;
                                }

                                write_needed = 0;
                        }
                        tmp_offset = start_idx + GF_DISK_SECTOR_SIZE;
                }

                if ((start_idx < buf_len) || write_needed) {

                        ret = syncop_write (to, fd, (buf + tmp_offset),
                                            (buf_len - tmp_offset),
                                            (offset + tmp_offset), iobref);
                        if (ret < 0) {

                                gf_log (THIS->name, GF_LOG_WARNING,
                                        "failed to write (%s)",
                                        strerror (errno));
                                goto out;
                        }
                }

                size_pending = (size - buf_len);
                if (!size_pending)
                        break;
        }

        ret = size;
out:
        return ret;

}
