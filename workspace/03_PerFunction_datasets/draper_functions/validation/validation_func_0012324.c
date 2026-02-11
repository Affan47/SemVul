sh_loop_read_cbk (call_frame_t *loop_frame, void *cookie,
                  xlator_t *this, int32_t op_ret, int32_t op_errno,
                  struct iovec *vector, int32_t count, struct iatt *buf,
                  struct iobref *iobref)
{
        afr_private_t *               priv       = NULL;
        afr_local_t *                 loop_local   = NULL;
        afr_self_heal_t *             loop_sh      = NULL;
        call_frame_t                 *sh_frame   = NULL;
        int                           i          = 0;
        int                           call_count = 0;
        afr_local_t *                 sh_local   = NULL;
        afr_self_heal_t *             sh      = NULL;

        priv       = this->private;
        loop_local = loop_frame->local;
        loop_sh    = &loop_local->self_heal;

        sh_frame = loop_sh->sh_frame;
        sh_local = sh_frame->local;
        sh       = &sh_local->self_heal;

        gf_log (this->name, GF_LOG_TRACE,
                "read %d bytes of data from %s, offset %"PRId64"",
                op_ret, loop_local->loc.path, loop_sh->offset);

        if (op_ret <= 0) {
                if (op_ret < 0) {
                        sh->op_failed = 1;
                        gf_log (this->name, GF_LOG_ERROR, "read failed on %d "
                                "for %s reason :%s", sh->source,
                                sh_local->loc.path, strerror (errno));
                } else {
                        sh->eof_reached = _gf_true;
                        gf_log (this->name, GF_LOG_DEBUG, "Eof reached for %s",
                                sh_local->loc.path);
                }
                sh_loop_return (sh_frame, this, loop_frame, op_ret, op_errno);
                goto out;
        }

        if (loop_sh->file_has_holes && iov_0filled (vector, count) == 0) {
                        gf_log (this->name, GF_LOG_DEBUG, "0 filled block");
                        sh_loop_return (sh_frame, this, loop_frame,
                                        op_ret, op_errno);
                        goto out;
        }

        call_count = sh_number_of_writes_needed (loop_sh->write_needed,
                                                 priv->child_count);
        GF_ASSERT (call_count > 0);
        loop_local->call_count = call_count;

        for (i = 0; i < priv->child_count; i++) {
                if (!loop_sh->write_needed[i])
                        continue;
                STACK_WIND_COOKIE (loop_frame, sh_loop_write_cbk,
                                   (void *) (long) i,
                                   priv->children[i],
                                   priv->children[i]->fops->writev,
                                   loop_sh->healing_fd, vector, count,
                                   loop_sh->offset, iobref);

                if (!--call_count)
                        break;
        }

out:
        return 0;
}
