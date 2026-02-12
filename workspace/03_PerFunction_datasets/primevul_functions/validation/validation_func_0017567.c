virSecuritySELinuxRestoreFileLabel(virSecurityManager *mgr,
                                   const char *path,
                                   bool recall)
{
    bool privileged = virSecurityManagerGetPrivileged(mgr);
    struct stat buf;
    char *fcon = NULL;
    char *newpath = NULL;
    int rc;
    int ret = -1;


    if (!path)
        return 0;

    VIR_INFO("Restoring SELinux context on '%s'", path);

    if (virFileResolveLink(path, &newpath) < 0) {
        VIR_WARN("cannot resolve symlink %s: %s", path,
                 g_strerror(errno));
        goto cleanup;
    }

    if ((rc = virSecuritySELinuxTransactionAppend(path, NULL,
                                                  recall, true)) < 0) {
        goto cleanup;
    } else if (rc > 0) {
        ret = 0;
        goto cleanup;
    }

    if (recall) {
        rc = virSecuritySELinuxRecallLabel(newpath, &fcon);
        if (rc == -2) {

        } else if (rc < 0) {
            goto cleanup;
        } else if (rc > 0) {
            ret = 0;
            goto cleanup;
        }
    }

    if (!recall || rc == -2) {
        if (stat(newpath, &buf) != 0) {
            VIR_WARN("cannot stat %s: %s", newpath,
                     g_strerror(errno));
            goto cleanup;
        }

        if (getContext(mgr, newpath, buf.st_mode, &fcon) < 0) {


            VIR_WARN("cannot lookup default selinux label for %s", newpath);
            ret = 0;
            goto cleanup;
        }
    }

    if (virSecuritySELinuxSetFileconImpl(newpath, fcon, privileged) < 0)
        goto cleanup;

    ret = 0;
 cleanup:
    freecon(fcon);
    VIR_FREE(newpath);
    return ret;
}
