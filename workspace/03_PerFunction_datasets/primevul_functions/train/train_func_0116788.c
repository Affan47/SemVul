qemuProcessInit(virQEMUDriverPtr driver,
                virDomainObjPtr vm,
                virCPUDefPtr updatedCPU,
                qemuDomainAsyncJob asyncJob,
                bool migration,
                unsigned int flags)
{
    qemuDomainObjPrivatePtr priv = vm->privateData;
    int stopFlags;
    virCPUDefPtr origCPU = NULL;
    int ret = -1;

    VIR_DEBUG("vm=%p name=%s id=%d migration=%d",
              vm, vm->def->name, vm->def->id, migration);

    VIR_DEBUG("Beginning VM startup process");

    if (virDomainObjIsActive(vm)) {
        virReportError(VIR_ERR_OPERATION_INVALID, "%s",
                       _("VM is already active"));
        goto cleanup;
    }


    if (vm->def->postParseFailed) {
        VIR_DEBUG("re-running the post parse callback");


        if (virDomainDefPostParse(vm->def, 0, driver->xmlopt, NULL) < 0)
            goto cleanup;
    }

    VIR_DEBUG("Determining emulator version");
    if (qemuProcessPrepareQEMUCaps(vm, driver->qemuCapsCache, flags) < 0)
        goto cleanup;

    if (qemuDomainUpdateCPU(vm, updatedCPU, &origCPU) < 0)
        goto cleanup;

    if (qemuProcessStartValidate(driver, vm, priv->qemuCaps, flags) < 0)
        goto cleanup;


    VIR_DEBUG("Setting current domain def as transient");
    if (virDomainObjSetDefTransient(driver->xmlopt, vm, priv->qemuCaps) < 0)
        goto cleanup;


    priv->inhibitDiskTransientDelete = true;

    if (flags & VIR_QEMU_PROCESS_START_PRETEND) {
        if (qemuDomainSetPrivatePaths(driver, vm) < 0) {
            virDomainObjRemoveTransientDef(vm);
            goto cleanup;
        }
    } else {
        vm->def->id = qemuDriverAllocateID(driver);
        qemuDomainSetFakeReboot(driver, vm, false);
        virDomainObjSetState(vm, VIR_DOMAIN_PAUSED, VIR_DOMAIN_PAUSED_STARTING_UP);

        if (g_atomic_int_add(&driver->nactive, 1) == 0 && driver->inhibitCallback)
            driver->inhibitCallback(true, driver->inhibitOpaque);


        if (qemuProcessStartHook(driver, vm,
                                 VIR_HOOK_QEMU_OP_PREPARE,
                                 VIR_HOOK_SUBOP_BEGIN) < 0)
            goto stop;

        if (qemuDomainSetPrivatePaths(driver, vm) < 0)
            goto stop;

        priv->origCPU = g_steal_pointer(&origCPU);
    }

    ret = 0;

 cleanup:
    virCPUDefFree(origCPU);
    return ret;

 stop:
    stopFlags = VIR_QEMU_PROCESS_STOP_NO_RELABEL;
    if (migration)
        stopFlags |= VIR_QEMU_PROCESS_STOP_MIGRATED;
    qemuProcessStop(driver, vm, VIR_DOMAIN_SHUTOFF_FAILED, asyncJob, stopFlags);
    goto cleanup;
}
