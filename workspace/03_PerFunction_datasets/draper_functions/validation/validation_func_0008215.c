mdc_fgetxattr (call_frame_t *frame, xlator_t *this, fd_t *fd, const char *key,
               dict_t *xdata)
{
        int           ret;
        mdc_local_t  *local = NULL;
	dict_t       *xattr = NULL;
	int           op_errno = ENODATA;

        local = mdc_local_get (frame);
        if (!local)
                goto uncached;

        local->fd = fd_ref (fd);

	if (!is_mdc_key_satisfied (key))
		goto uncached;

	ret = mdc_inode_xatt_get (this, fd->inode, &xattr);
	if (ret != 0)
		goto uncached;

	if (!xattr || !dict_get (xattr, (char *)key)) {
		ret = -1;
		op_errno = ENODATA;
	}

        MDC_STACK_UNWIND (fgetxattr, frame, ret, op_errno, xattr, xdata);

        return 0;

uncached:
        STACK_WIND (frame, mdc_fgetxattr_cbk,
                    FIRST_CHILD(this), FIRST_CHILD(this)->fops->fgetxattr,
                    fd, key, xdata);
        return 0;
}
