trace_ftruncate (call_frame_t *frame, xlator_t *this,
                 fd_t *fd, off_t offset, dict_t *xdata)
{
        if (trace_fop_names[GF_FOP_FTRUNCATE].enabled) {
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": gfid=%s offset=%"PRId64" fd=%p",
                        frame->root->unique, uuid_utoa (fd->inode->gfid),
                        offset, fd);
                frame->local = fd->inode->gfid;
        }

        STACK_WIND (frame, trace_ftruncate_cbk,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->ftruncate,
                    fd, offset, xdata);

        return 0;
}
