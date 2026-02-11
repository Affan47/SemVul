__dht_check_free_space (xlator_t *to, xlator_t *from, loc_t *loc,
                        struct iatt *stbuf, int flag)
{
        struct statvfs  src_statfs = {0,};
        struct statvfs  dst_statfs = {0,};
        int             ret        = -1;
        xlator_t       *this       = NULL;

        uint64_t        src_statfs_blocks = 1;
        uint64_t        dst_statfs_blocks = 1;

        this = THIS;

        ret = syncop_statfs (from, loc, &src_statfs);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR,
                        "failed to get statfs of %s on %s (%s)",
                        loc->path, from->name, strerror (errno));
                goto out;
        }

        ret = syncop_statfs (to, loc, &dst_statfs);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR,
                        "failed to get statfs of %s on %s (%s)",
                        loc->path, to->name, strerror (errno));
                goto out;
        }


        if (flag != GF_DHT_MIGRATE_DATA)
                goto check_avail_space;


        if (stbuf) {
                dst_statfs_blocks = ((dst_statfs.f_bavail *
                                      dst_statfs.f_bsize) /
                                     GF_DISK_SECTOR_SIZE);
                src_statfs_blocks = ((src_statfs.f_bavail *
                                      src_statfs.f_bsize) /
                                     GF_DISK_SECTOR_SIZE);
                if ((dst_statfs_blocks - stbuf->ia_blocks) <
                    (src_statfs_blocks + stbuf->ia_blocks)) {
                        gf_log (this->name, GF_LOG_WARNING,
                                "data movement attempted from node (%s) with"
                                " higher disk space to a node (%s) with "
                                "lesser disk space (%s)", from->name,
                                to->name, loc->path);


                        ret = 1;
                        goto out;
                }
        }
check_avail_space:
        if (((dst_statfs.f_bavail * dst_statfs.f_bsize) /
              GF_DISK_SECTOR_SIZE) < stbuf->ia_blocks) {
                gf_log (this->name, GF_LOG_ERROR,
                        "data movement attempted from node (%s) with "
                        "to node (%s) which does not have required free space"
                        " for %s", from->name, to->name, loc->path);
                ret = 1;
                goto out;
        }

        ret = 0;
out:
        return ret;
}
