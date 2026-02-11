afr_mknod_wind (call_frame_t *frame, xlator_t *this)
{
        afr_local_t *local = NULL;
        afr_private_t *priv = NULL;
        int call_count = -1;
        int i = 0;

        local = frame->local;
        priv  = this->private;

        call_count = afr_pre_op_done_children_count (local->transaction.pre_op,
                                                     priv->child_count);

        if (call_count == 0) {
                local->transaction.resume (frame, this);
                return 0;
        }

        local->call_count = call_count;

        for (i = 0; i < priv->child_count; i++) {
                if (local->transaction.pre_op[i]) {
                        STACK_WIND_COOKIE (frame, afr_mknod_wind_cbk, (void *) (long) i,
                                           priv->children[i],
                                           priv->children[i]->fops->mknod,
                                           &local->loc, local->cont.mknod.mode,
                                           local->cont.mknod.dev,
                                           local->cont.mknod.params);
                        if (!--call_count)
                                break;
                }
        }

        return 0;
}
