qemuProcessQEMULabelUniqPath(qemuProcessQMPPtr proc)
{

    if (chown(proc->uniqDir, proc->runUid, -1) < 0) {
        virReportSystemError(errno,
                             _("Cannot chown uniq path: %s"),
                             proc->uniqDir);
        return -1;
    }

    return 0;
}
