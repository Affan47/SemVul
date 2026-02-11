afr_create_wind_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno,
                     fd_t *fd, inode_t *inode, struct iatt *buf,
                     struct iatt *preparent, struct iatt *postparent,
                     dict_t *xdata)
{
        afr_local_t     *local = NULL;
        uint64_t        ctx = 0;
        afr_fd_ctx_t    *fd_ctx = NULL;
        int             ret = 0;
        int             call_count = -1;
        int             child_index = -1;

        local = frame->local;

        child_index = (long) cookie;

        LOCK (&frame->lock);
        {
                if (op_ret > -1) {
                        ret = afr_fd_ctx_set (this, fd);
                        if (ret < 0) {
                                gf_log (this->name, GF_LOG_ERROR,
                                        "could not set ctx on fd=%p", fd);

                                local->op_ret   = -1;
                                local->op_errno = -ret;
                                goto unlock;
                        }

                        ret = fd_ctx_get (fd, this, &ctx);
                        if (ret < 0) {
                                gf_log (this->name, GF_LOG_ERROR,
                                        "could not get fd ctx for fd=%p", fd);
                                local->op_ret   = -1;
                                local->op_errno = -ret;
                                goto unlock;
                        }

                        fd_ctx = (afr_fd_ctx_t *)(long) ctx;

                        fd_ctx->opened_on[child_index] = AFR_FD_OPENED;
                        fd_ctx->flags                  = local->cont.create.flags;

                        if (local->success_count == 0) {
				if (xdata)
					local->xdata_rsp = dict_ref(xdata);
			}
                }
                __dir_entry_fop_common_cbk (frame, child_index, this,
                                            op_ret, op_errno, inode, buf,
                                            preparent, postparent, NULL, NULL);
        }

unlock:
        UNLOCK (&frame->lock);

        call_count = afr_frame_return (frame);

        if (call_count == 0)
                afr_dir_fop_done (frame, this);

        return 0;
}
