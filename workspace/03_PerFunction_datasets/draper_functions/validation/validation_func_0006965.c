quota_fsetxattr (call_frame_t *frame, xlator_t *this, fd_t *fd,
                 dict_t *dict, int flags, dict_t *xdata)
{
        data_pair_t    *trav     = NULL;
        int32_t         op_ret   = -1;
        int32_t         op_errno = EINVAL;

        VALIDATE_OR_GOTO (frame, err);
        VALIDATE_OR_GOTO (this, err);
        VALIDATE_OR_GOTO (fd, err);

        GF_IF_INTERNAL_XATTR_GOTO ("trusted.glusterfs.quota*", dict,
                                   trav, op_errno, err);

        STACK_WIND (frame, quota_fsetxattr_cbk,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fsetxattr,
                    fd, dict, flags, xdata);
        return 0;
 err:
        QUOTA_STACK_UNWIND (fsetxattr, frame, op_ret, op_errno, NULL);
        return 0;
}
