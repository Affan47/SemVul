virSecuritySELinuxSetFilecon(virSecurityManager *mgr,
                             const char *path,
                             const char *tcon,
                             bool remember)
{
    bool privileged = virSecurityManagerGetPrivileged(mgr);
    char *econ = NULL;
    int refcount;
    int rc;
    bool rollback = false;
    int ret = -1;

    if ((rc = virSecuritySELinuxTransactionAppend(path, tcon,
                                                  remember, false)) < 0)
        return -1;
    else if (rc > 0)
        return 0;

    if (remember) {
        if (getfilecon_raw(path, &econ) < 0 &&
            errno != ENOTSUP && errno != ENODATA) {
            virReportSystemError(errno,
                                 _("unable to get SELinux context of %s"),
                                 path);
            goto cleanup;
        }

        if (econ) {
            refcount = virSecuritySELinuxRememberLabel(path, econ);
            if (refcount > 0)
                rollback = true;
            if (refcount == -2) {

            } else if (refcount < 0) {
                goto cleanup;
            } else if (refcount > 1) {


                if (STRNEQ(econ, tcon)) {
                    virReportError(VIR_ERR_OPERATION_INVALID,
                                   _("Setting different SELinux label on %s "
                                     "which is already in use"), path);
                    goto cleanup;
                }
            }
        }
    }

    rc = virSecuritySELinuxSetFileconImpl(path, tcon, privileged);
    if (rc < 0)
        goto cleanup;


    if (rc == 0)
        rollback = false;

    ret = 0;
 cleanup:
    if (rollback) {
        virErrorPtr origerr;

        virErrorPreserveLast(&origerr);


        if (virSecuritySELinuxRestoreFileLabel(mgr, path, remember) < 0)
            VIR_WARN("Unable to restore label on '%s'. "
                     "XATTRs might have been left in inconsistent state.",
                     path);

        virErrorRestore(&origerr);

    }
    freecon(econ);
    return ret;
}
