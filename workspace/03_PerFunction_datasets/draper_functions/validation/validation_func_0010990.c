fuse_fsync_resume (fuse_state_t *state)
{
        gf_log ("glusterfs-fuse", GF_LOG_TRACE,
                "%"PRIu64": FSYNC %p", state->finh->unique,
		state->fd);


        FUSE_FOP (state, fuse_fsync_cbk, GF_FOP_FSYNC,
                  fsync, state->fd, (state->flags & 1), state->xdata);
}
