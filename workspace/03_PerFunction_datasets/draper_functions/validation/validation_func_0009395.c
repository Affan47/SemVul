ra_flush (call_frame_t *frame, xlator_t *this, fd_t *fd)
{
        ra_file_t *file     = NULL;
        uint64_t   tmp_file = 0;
        int32_t    op_errno = EINVAL;

        GF_ASSERT (frame);
        GF_VALIDATE_OR_GOTO (frame->this->name, this, unwind);
        GF_VALIDATE_OR_GOTO (frame->this->name, fd, unwind);

        fd_ctx_get (fd, this, &tmp_file);

        file = (ra_file_t *)(long)tmp_file;
        if (file == NULL) {
                op_errno = EBADF;
                gf_log (this->name, GF_LOG_WARNING,
                        "flush received on fd (%p) with no"
                        " file set in its context", fd);
                goto unwind;
        }

        flush_region (frame, file, 0, file->pages.prev->offset+1);

        STACK_WIND (frame, ra_flush_cbk, FIRST_CHILD (this),
                    FIRST_CHILD (this)->fops->flush, fd);
        return 0;

unwind:
        STACK_UNWIND_STRICT (flush, frame, -1, op_errno);
        return 0;
}
