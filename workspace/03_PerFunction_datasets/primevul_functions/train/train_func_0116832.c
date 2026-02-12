qemuProcessPrepareQEMUCaps(virDomainObjPtr vm,
                           virFileCachePtr qemuCapsCache,
                           unsigned int processStartFlags)
{
    qemuDomainObjPrivatePtr priv = vm->privateData;

    virObjectUnref(priv->qemuCaps);
    if (!(priv->qemuCaps = virQEMUCapsCacheLookupCopy(qemuCapsCache,
                                                      vm->def->virtType,
                                                      vm->def->emulator,
                                                      vm->def->os.machine)))
        return -1;

    if (processStartFlags & VIR_QEMU_PROCESS_START_STANDALONE)
        virQEMUCapsClear(priv->qemuCaps, QEMU_CAPS_CHARDEV_FD_PASS);


    if (qemuProcessStartUpdateCustomCaps(vm) < 0)
        return -1;


    virQEMUCapsInitProcessCapsInterlock(priv->qemuCaps);

    return 0;
}
