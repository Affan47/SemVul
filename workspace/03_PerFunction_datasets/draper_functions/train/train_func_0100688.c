get_call_frame_for_req (fuse_state_t *state)
{
        call_pool_t           *pool = NULL;
        fuse_in_header_t      *finh = NULL;
        call_frame_t          *frame = NULL;
        xlator_t              *this = NULL;
        fuse_private_t        *priv = NULL;

        pool = state->pool;
        finh = state->finh;
        this = state->this;
        priv = this->private;

        frame = create_frame (this, pool);
        if (!frame)
                return NULL;

        if (finh) {
                frame->root->uid      = finh->uid;
                frame->root->gid      = finh->gid;
                frame->root->pid      = finh->pid;
                frame->root->unique   = finh->unique;
                set_lk_owner_from_uint64 (&frame->root->lk_owner,
                                          state->lk_owner);
        }

        frame_fill_groups (frame);

        if (priv && priv->client_pid_set)
                frame->root->pid = priv->client_pid;

        frame->root->type = GF_OP_TYPE_FOP;

        return frame;
}
