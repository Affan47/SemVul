switch_mknod_linkfile_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                           int op_ret, int op_errno, inode_t *inode,
                           struct iatt *stbuf, struct iatt *preparent,
                           struct iatt *postparent, dict_t *xdata)
{
        dht_local_t  *local = NULL;

        local = frame->local;
        if (!local || !local->cached_subvol) {
                op_errno = EINVAL;
                op_ret = -1;
                goto err;
        }

        if (op_ret >= 0) {
                STACK_WIND_COOKIE (frame, dht_newfile_cbk,
                            (void *)local->cached_subvol, local->cached_subvol,
                            local->cached_subvol->fops->mknod,
                            &local->loc, local->mode, local->rdev,
                            local->umask, local->params);

                return 0;
        }
err:
        DHT_STACK_UNWIND (link, frame, op_ret, op_errno,
                          inode, stbuf, preparent, postparent, xdata);
        return 0;
}
