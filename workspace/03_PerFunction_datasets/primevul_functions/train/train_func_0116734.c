qemuProcessPrepareDomain(virQEMUDriverPtr driver,
                         virDomainObjPtr vm,
                         unsigned int flags)
{
    size_t i;
    qemuDomainObjPrivatePtr priv = vm->privateData;
    g_autoptr(virQEMUDriverConfig) cfg = virQEMUDriverGetConfig(driver);

    priv->machineName = qemuDomainGetMachineName(vm);
    if (!priv->machineName)
        return -1;

    if (!(flags & VIR_QEMU_PROCESS_START_PRETEND)) {


        VIR_DEBUG("Generating domain security label (if required)");
        if (qemuSecurityGenLabel(driver->securityManager, vm->def) < 0) {
            virDomainAuditSecurityLabel(vm, false);
            return -1;
        }
        virDomainAuditSecurityLabel(vm, true);

        if (qemuProcessPrepareDomainNUMAPlacement(vm) < 0)
            return -1;
    }


    if (cfg->stdioLogD &&
        virQEMUCapsGet(priv->qemuCaps, QEMU_CAPS_CHARDEV_FILE_APPEND)) {
        priv->chardevStdioLogd = true;
    }


    priv->rememberOwner = cfg->rememberOwner;

    qemuProcessPrepareAllowReboot(vm);


    VIR_DEBUG("Assigning domain PCI addresses");
    if ((qemuDomainAssignAddresses(vm->def, priv->qemuCaps, driver, vm,
                                   !!(flags & VIR_QEMU_PROCESS_START_NEW))) < 0) {
        return -1;
    }

    if (qemuAssignDeviceAliases(vm->def, priv->qemuCaps) < 0)
        return -1;

    VIR_DEBUG("Setting graphics devices");
    if (qemuProcessSetupGraphics(driver, vm, priv->qemuCaps, flags) < 0)
        return -1;

    VIR_DEBUG("Create domain masterKey");
    if (qemuDomainMasterKeyCreate(vm) < 0)
        return -1;

    VIR_DEBUG("Setting up storage");
    if (qemuProcessPrepareDomainStorage(driver, vm, priv, cfg, flags) < 0)
        return -1;

    VIR_DEBUG("Setting up host devices");
    if (qemuProcessPrepareDomainHostdevs(vm, priv) < 0)
        return -1;

    VIR_DEBUG("Prepare chardev source backends for TLS");
    qemuDomainPrepareChardevSource(vm->def, cfg);

    VIR_DEBUG("Prepare device secrets");
    if (qemuDomainSecretPrepare(driver, vm) < 0)
        return -1;

    VIR_DEBUG("Prepare bios/uefi paths");
    if (qemuFirmwareFillDomain(driver, vm->def, flags) < 0)
        return -1;
    if (qemuDomainInitializePflashStorageSource(vm) < 0)
        return -1;

    VIR_DEBUG("Preparing external devices");
    if (qemuExtDevicesPrepareDomain(driver, vm) < 0)
        return -1;

    if (flags & VIR_QEMU_PROCESS_START_NEW) {
        VIR_DEBUG("Aligning guest memory");
        if (qemuDomainAlignMemorySizes(vm->def) < 0)
            return -1;
    }

    for (i = 0; i < vm->def->nchannels; i++) {
        if (qemuDomainPrepareChannel(vm->def->channels[i],
                                     priv->channelTargetDir) < 0)
            return -1;
    }

    if (!(priv->monConfig = virDomainChrSourceDefNew(driver->xmlopt)))
        return -1;

    VIR_DEBUG("Preparing monitor state");
    if (qemuProcessPrepareMonitorChr(priv->monConfig, priv->libDir) < 0)
        return -1;

    priv->monError = false;
    priv->monStart = 0;
    priv->runningReason = VIR_DOMAIN_RUNNING_UNKNOWN;
    priv->pausedReason = VIR_DOMAIN_PAUSED_UNKNOWN;

    VIR_DEBUG("Updating guest CPU definition");
    if (qemuProcessUpdateGuestCPU(vm->def, priv->qemuCaps, driver->hostarch, flags) < 0)
        return -1;

    for (i = 0; i < vm->def->nshmems; i++)
        qemuDomainPrepareShmemChardev(vm->def->shmems[i]);

    if (vm->def->sev) {
        VIR_DEBUG("Updating SEV platform info");
        if (qemuProcessUpdateSEVInfo(vm) < 0)
            return -1;
    }

    return 0;
}
