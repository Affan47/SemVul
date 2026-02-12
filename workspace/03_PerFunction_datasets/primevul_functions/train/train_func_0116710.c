qemuProcessRefreshCPU(virQEMUDriverPtr driver,
                      virDomainObjPtr vm)
{
    qemuDomainObjPrivatePtr priv = vm->privateData;
    g_autoptr(virCPUDef) host = NULL;
    g_autoptr(virCPUDef) hostmig = NULL;
    g_autoptr(virCPUDef) cpu = NULL;

    if (!virQEMUCapsGuestIsNative(driver->hostarch, vm->def->os.arch))
        return 0;

    if (!vm->def->cpu)
        return 0;

    if (qemuProcessRefreshCPUMigratability(driver, vm, QEMU_ASYNC_JOB_NONE) < 0)
        return -1;

    if (!(host = virQEMUDriverGetHostCPU(driver))) {
        virResetLastError();
        return 0;
    }


    if (vm->def->cpu->mode == VIR_CPU_MODE_HOST_MODEL) {


        if (qemuDomainIsPSeries(vm->def))
            return 0;

        if (!(hostmig = virCPUCopyMigratable(host->arch, host)))
            return -1;

        if (!(cpu = virCPUDefCopyWithoutModel(hostmig)) ||
            virCPUDefCopyModelFilter(cpu, hostmig, false,
                                     virQEMUCapsCPUFilterFeatures,
                                     &host->arch) < 0)
            return -1;

        if (virCPUUpdate(vm->def->os.arch, vm->def->cpu, cpu) < 0)
            return -1;

        if (qemuProcessUpdateCPU(driver, vm, QEMU_ASYNC_JOB_NONE) < 0)
            return -1;
    } else if (!virQEMUCapsGet(priv->qemuCaps, QEMU_CAPS_QUERY_CPU_MODEL_EXPANSION)) {


        if (qemuDomainFixupCPUs(vm, &priv->origCPU) < 0)
            return -1;
    }

    return 0;
}
