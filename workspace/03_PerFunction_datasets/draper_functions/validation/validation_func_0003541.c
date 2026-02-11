dht_lookup_selfheal_cbk (call_frame_t *frame, void *cookie,
                         xlator_t *this,
                         int op_ret, int op_errno, dict_t *xdata)
{
        dht_local_t  *local = NULL;
        dht_layout_t *layout = NULL;
	int           ret = -1;

        GF_VALIDATE_OR_GOTO ("dht", frame, out);
        GF_VALIDATE_OR_GOTO ("dht", this, out);
        GF_VALIDATE_OR_GOTO ("dht", frame->local, out);

        local = frame->local;
        ret = op_ret;

        FRAME_SU_UNDO (frame, dht_local_t);

        if (ret == 0) {
                layout = local->selfheal.layout;
                ret = dht_layout_set (this, local->inode, layout);
        }

        WIPE (&local->postparent);

        DHT_STRIP_PHASE1_FLAGS (&local->stbuf);

        DHT_STACK_UNWIND (lookup, frame, ret, local->op_errno, local->inode,
                          &local->stbuf, local->xattr, &local->postparent);

out:
        return ret;
}
