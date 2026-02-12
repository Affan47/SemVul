qemuProcessQMPInit(qemuProcessQMPPtr proc)
{
    g_autofree char *template = NULL;

    VIR_DEBUG("proc=%p, emulator=%s", proc, proc->binary);

    template = g_strdup_printf("%s/qmp-XXXXXX", proc->libDir);

    if (!(proc->uniqDir = g_mkdtemp(template))) {
        virReportSystemError(errno,
                             _("Failed to create unique directory with "
                               "template '%s' for probing QEMU"),
                             template);
        return -1;
    }


    template = NULL;

    if (qemuProcessQEMULabelUniqPath(proc) < 0)
        return -1;

    proc->monpath = g_strdup_printf("%s/%s", proc->uniqDir, "qmp.monitor");

    proc->monarg = g_strdup_printf("unix:%s,server,nowait", proc->monpath);


    proc->pidfile = g_strdup_printf("%s/%s", proc->uniqDir, "qmp.pid");

    return 0;
}
