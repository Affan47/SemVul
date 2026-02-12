qemuProcessWaitForMonitor(virQEMUDriverPtr driver,
                          virDomainObjPtr vm,
                          int asyncJob,
                          qemuDomainLogContextPtr logCtxt)
{
    int ret = -1;
    GHashTable *info = NULL;
    qemuDomainObjPrivatePtr priv = vm->privateData;
    bool retry = true;

    if (priv->qemuCaps &&
        virQEMUCapsGet(priv->qemuCaps, QEMU_CAPS_CHARDEV_FD_PASS))
        retry = false;

    VIR_DEBUG("Connect monitor to vm=%p name='%s' retry=%d",
              vm, vm->def->name, retry);

    if (qemuConnectMonitor(driver, vm, asyncJob, retry, logCtxt) < 0)
        goto cleanup;


    if (qemuDomainObjEnterMonitorAsync(driver, vm, asyncJob) < 0)
        goto cleanup;
    ret = qemuMonitorGetChardevInfo(priv->mon, &info);
    VIR_DEBUG("qemuMonitorGetChardevInfo returned %i", ret);
    if (qemuDomainObjExitMonitor(driver, vm) < 0)
        ret = -1;

    if (ret == 0) {
        if ((ret = qemuProcessFindCharDevicePTYsMonitor(vm, info)) < 0)
            goto cleanup;

         qemuProcessRefreshChannelVirtioState(driver, vm, info, true);
    }

 cleanup:
    virHashFree(info);

    if (logCtxt && kill(vm->pid, 0) == -1 && errno == ESRCH) {
        qemuProcessReportLogError(logCtxt,
                                  _("process exited while connecting to monitor"));
        ret = -1;
    }

    return ret;
}
