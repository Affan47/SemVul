virSecuritySELinuxRestoreImageLabelSingle(virSecurityManager *mgr,
                                          virDomainDef *def,
                                          virStorageSource *src,
                                          bool migrated)
{
    virSecurityLabelDef *seclabel;
    virSecurityDeviceLabelDef *disk_seclabel;
    g_autofree char *vfioGroupDev = NULL;
    const char *path = src->path;

    seclabel = virDomainDefGetSecurityLabelDef(def, SECURITY_SELINUX_NAME);
    if (seclabel == NULL)
        return 0;

    disk_seclabel = virStorageSourceGetSecurityLabelDef(src,
                                                        SECURITY_SELINUX_NAME);
    if (!seclabel->relabel || (disk_seclabel && !disk_seclabel->relabel))
        return 0;


    if (disk_seclabel && disk_seclabel->labelskip &&
        !virStorageSourceHasBacking(src))
        return 0;


    if (src->readonly || src->shared)
        return 0;


    if (migrated) {
        int rc = 1;

        if (virStorageSourceIsLocalStorage(src)) {
            if (!src->path)
                return 0;

            if ((rc = virFileIsSharedFS(src->path)) < 0)
                return -1;
        }

        if (rc == 1) {
            VIR_DEBUG("Skipping image label restore on %s because FS is shared",
                      src->path);
            return 0;
        }
    }


    if (src->type == VIR_STORAGE_TYPE_NVME) {
        const virStorageSourceNVMeDef *nvme = src->nvme;

        if (!(vfioGroupDev = virPCIDeviceAddressGetIOMMUGroupDev(&nvme->pciAddr)))
            return -1;


        path = vfioGroupDev;
    }

    return virSecuritySELinuxRestoreFileLabel(mgr, path, true);
}
