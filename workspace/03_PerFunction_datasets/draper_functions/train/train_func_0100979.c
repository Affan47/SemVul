io_stats_rename (call_frame_t *frame, xlator_t *this,
                 loc_t *oldloc, loc_t *newloc, dict_t *xdata)
{
        START_FOP_LATENCY (frame);

        STACK_WIND (frame, io_stats_rename_cbk,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->rename,
                    oldloc, newloc, xdata);
        return 0;
}
