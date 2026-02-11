__is_lower_locked (call_frame_t *frame, xlator_t *this)
{
        afr_internal_lock_t *int_lock = NULL;
        afr_private_t       *priv     = NULL;
        afr_local_t         *local    = NULL;
        int count = 0;
        int i     = 0;

        local    = frame->local;
        int_lock = &local->internal_lock;
        priv     = this->private;

        for (i = 0; i < priv->child_count; i++) {
                if (int_lock->lower_locked_nodes[i] & LOCKED_LOWER)
                        count++;
        }

        return count;

}
