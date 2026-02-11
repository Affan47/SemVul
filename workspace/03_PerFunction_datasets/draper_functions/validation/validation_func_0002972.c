io_stats_writev_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno,
                     struct iatt *prebuf, struct iatt *postbuf, dict_t *xdata)
{
        struct ios_stat *iosstat = NULL;
        inode_t         *inode   = NULL;

        UPDATE_PROFILE_STATS (frame, WRITE);
        if (frame->local){
                inode = frame->local;
                frame->local = NULL;
                ios_inode_ctx_get (inode, this, &iosstat);
                if (iosstat) {
                        BUMP_STATS (iosstat, IOS_STATS_TYPE_WRITE);
                        BUMP_THROUGHPUT (iosstat, IOS_STATS_THRU_WRITE);
                        inode = NULL;
                        iosstat = NULL;
                }
        }

        STACK_UNWIND_STRICT (writev, frame, op_ret, op_errno, prebuf, postbuf, xdata);
        return 0;

}
