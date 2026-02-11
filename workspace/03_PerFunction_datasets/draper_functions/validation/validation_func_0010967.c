afr_sh_entry_impunge_all (call_frame_t *frame, xlator_t *this)
{
        afr_private_t   *priv = NULL;
        afr_local_t     *local  = NULL;
        afr_self_heal_t *sh  = NULL;
        int              active_src = -1;

        priv = this->private;
        local = frame->local;
        sh = &local->self_heal;

        sh->offset = 0;

        active_src = next_active_source (frame, this, sh->active_source);
        sh->active_source = active_src;

        if (sh->op_failed) {
                afr_sh_entry_finish (frame, this);
                return 0;
        }

        if (active_src == -1) {

                afr_sh_entry_erase_pending (frame, this);
                return 0;
        }

        gf_log (this->name, GF_LOG_TRACE,
                "impunging entries of %s on %s to other sinks",
                local->loc.path, priv->children[active_src]->name);

        afr_sh_entry_impunge_subvol (frame, this, active_src);

        return 0;
}
