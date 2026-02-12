virSecuritySELinuxSetFileconImpl(const char *path,
                                 const char *tcon,
                                 bool privileged)
{


    VIR_INFO("Setting SELinux context on '%s' to '%s'", path, tcon);

    if (setfilecon_raw(path, (const char *)tcon) < 0) {
        int setfilecon_errno = errno;


        VIR_WARNINGS_NO_WLOGICALOP_EQUAL_EXPR
        if (setfilecon_errno != EOPNOTSUPP && setfilecon_errno != ENOTSUP &&
            setfilecon_errno != EROFS) {
        VIR_WARNINGS_RESET


            if (security_getenforce() == 1 &&
                (setfilecon_errno != EPERM || privileged)) {
                virReportSystemError(setfilecon_errno,
                                     _("unable to set security context '%s' on '%s'"),
                                     tcon, path);
                return -1;
            }
            VIR_WARN("unable to set security context '%s' on '%s' (errno %d)",
                     tcon, path, setfilecon_errno);
        } else {
            const char *msg;
            if (virFileIsSharedFSType(path, VIR_FILE_SHFS_NFS) == 1 &&
                security_get_boolean_active("virt_use_nfs") != 1) {
                msg = _("Setting security context '%s' on '%s' not supported. "
                        "Consider setting virt_use_nfs");
                if (security_getenforce() == 1)
                    VIR_WARN(msg, tcon, path);
                else
                    VIR_INFO(msg, tcon, path);
            } else {
                VIR_INFO("Setting security context '%s' on '%s' not supported",
                         tcon, path);
            }
        }

        return 1;
    }
    return 0;
}
