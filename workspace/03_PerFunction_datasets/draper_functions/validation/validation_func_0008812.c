fuse_mknod_resume (fuse_state_t *state)
{
        if (!state->loc.parent) {
                gf_log ("glusterfs-fuse", GF_LOG_ERROR,
                        "MKNOD %"PRId64"/%s (%s/%s) resolution failed",
                        state->finh->nodeid, state->resolve.bname,
                        uuid_utoa (state->resolve.gfid), state->resolve.bname);
                send_fuse_err (state->this, state->finh, ENOENT);
                free_fuse_state (state);
                return;
        }

        if (state->resolve.op_errno == ENOENT) {
                state->resolve.op_ret = 0;
                state->resolve.op_errno = 0;
        }

        if (state->loc.inode) {
                gf_log (state->this->name, GF_LOG_DEBUG, "inode already present");
                inode_unref (state->loc.inode);
                state->loc.inode = NULL;
        }

        state->loc.inode = inode_new (state->loc.parent->table);

        gf_log ("glusterfs-fuse", GF_LOG_TRACE,
                "%"PRIu64": MKNOD %s", state->finh->unique,
                state->loc.path);

        FUSE_FOP (state, fuse_newentry_cbk, GF_FOP_MKNOD,
                  mknod, &state->loc, state->mode, state->rdev, state->umask,
                  state->xdata);
}
