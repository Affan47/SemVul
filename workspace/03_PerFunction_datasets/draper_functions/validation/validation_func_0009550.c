quota_fgetxattr (call_frame_t *frame, xlator_t *this, fd_t *fd,
                 const char *name)
{
        int32_t ret     = 0;

        if (strcasecmp (name, "trusted.limit.list") == 0) {
                ret = quota_send_dir_limit_to_cli (frame, this, fd->inode,
                                                   name);
                if (ret == 0) {
                        return 0;
                }
        }

        STACK_WIND (frame, default_fgetxattr_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fgetxattr, fd, name);
        return 0;
}
