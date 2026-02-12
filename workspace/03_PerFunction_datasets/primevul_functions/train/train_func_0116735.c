qemuProcessInitCpuAffinity(virDomainObjPtr vm)
{
    bool settingAll = false;
    g_autoptr(virBitmap) cpumapToSet = NULL;
    virDomainNumatuneMemMode mem_mode;
    qemuDomainObjPrivatePtr priv = vm->privateData;

    if (!vm->pid) {
        virReportError(VIR_ERR_INTERNAL_ERROR, "%s",
                       _("Cannot setup CPU affinity until process is started"));
        return -1;
    }


    if (virDomainNumaGetNodeCount(vm->def->numa) <= 1 &&
        virDomainNumatuneGetMode(vm->def->numa, -1, &mem_mode) == 0 &&
        mem_mode == VIR_DOMAIN_NUMATUNE_MEM_STRICT) {
        virBitmapPtr nodeset = NULL;

        if (virDomainNumatuneMaybeGetNodeset(vm->def->numa,
                                             priv->autoNodeset,
                                             &nodeset,
                                             -1) < 0)
            return -1;

        if (virNumaNodesetToCPUset(nodeset, &cpumapToSet) < 0)
            return -1;
    } else if (vm->def->cputune.emulatorpin) {
        cpumapToSet = virBitmapNewCopy(vm->def->cputune.emulatorpin);
    } else {
        settingAll = true;
        if (qemuProcessGetAllCpuAffinity(&cpumapToSet) < 0)
            return -1;
    }


    if (cpumapToSet &&
        virProcessSetAffinity(vm->pid, cpumapToSet, settingAll) < 0) {
        return -1;
    }

    return 0;
}
