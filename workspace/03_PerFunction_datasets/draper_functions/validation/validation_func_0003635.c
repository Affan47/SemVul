syncop_fsync (xlator_t *subvol, fd_t *fd)
{
        struct syncargs args = {0, };

        SYNCOP (subvol, (&args), syncop_fsync_cbk, subvol->fops->fsync,
                fd, 0);

        errno = args.op_errno;
        return args.op_ret;

}
