fuse_mkdir (xlator_t *this, fuse_in_header_t *finh, void *msg)
{
        struct fuse_mkdir_in *fmi = msg;
        char *name = (char *)(fmi + 1);
        fuse_private_t *priv = NULL;

        fuse_state_t *state;
        int32_t ret = -1;

        GET_STATE (this, finh, state);

        uuid_generate (state->gfid);

	fuse_resolve_entry_init (state, &state->resolve, finh->nodeid, name);

        state->mode = fmi->mode;

        priv = this->private;
#if FUSE_KERNEL_MINOR_VERSION >=12
        if (priv->proto_minor >= 12)
                state->mode &= ~fmi->umask;
        if (priv->proto_minor >= 12 && priv->acl) {
                state->xdata = dict_new ();
                if (!state->xdata) {
                        gf_log ("glusterfs-fuse", GF_LOG_WARNING,
                                "MKDIR Failed to allocate a param dictionary");
                        send_fuse_err (this, finh, ENOMEM);
                        free_fuse_state (state);
                        return;
                }
                state->umask = fmi->umask;
                ret = dict_set_int16 (state->xdata, "umask", fmi->umask);
                if (ret < 0) {
                        gf_log ("glusterfs-fuse", GF_LOG_WARNING,
                                "MKDIR Failed adding umask to request");
                        dict_destroy (state->xdata);
                        send_fuse_err (this, finh, ENOMEM);
                        free_fuse_state (state);
                        return;
                }
                ret = dict_set_int16 (state->xdata, "mode", fmi->mode);
                if (ret < 0) {
                        gf_log ("glusterfs-fuse", GF_LOG_WARNING,
                                "MKDIR Failed adding mode to request");
                        dict_destroy (state->xdata);
                        send_fuse_err (this, finh, ENOMEM);
                        free_fuse_state (state);
                        return;
                }
        }
#endif

        fuse_resolve_and_resume (state, fuse_mkdir_resume);

        return;
}
