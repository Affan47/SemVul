virSecuritySELinuxSetImageLabelInternal(virSecurityManager *mgr,
                                        virDomainDef *def,
                                        virStorageSource *src,
                                        virStorageSource *parent,
                                        bool isChainTop)
{
    virSecuritySELinuxData *data = virSecurityManagerGetPrivateData(mgr);
    virSecurityLabelDef *secdef;
    virSecurityDeviceLabelDef *disk_seclabel;
    virSecurityDeviceLabelDef *parent_seclabel = NULL;
    char *use_label = NULL;
    bool remember;
    g_autofree char *vfioGroupDev = NULL;
    const char *path = src->path;
    int ret;

    if (!src->path || !virStorageSourceIsLocalStorage(src))
        return 0;

    secdef = virDomainDefGetSecurityLabelDef(def, SECURITY_SELINUX_NAME);
    if (!secdef || !secdef->relabel)
        return 0;


    remember = isChainTop && !src->readonly && !src->shared;

    disk_seclabel = virStorageSourceGetSecurityLabelDef(src,
                                                        SECURITY_SELINUX_NAME);
    parent_seclabel = virStorageSourceGetSecurityLabelDef(parent,
                                                          SECURITY_SELINUX_NAME);

    if (disk_seclabel && (!disk_seclabel->relabel || disk_seclabel->label)) {
        if (!disk_seclabel->relabel)
            return 0;

        use_label = disk_seclabel->label;
    } else if (parent_seclabel && (!parent_seclabel->relabel || parent_seclabel->label)) {
        if (!parent_seclabel->relabel)
            return 0;

        use_label = parent_seclabel->label;
    } else if (parent == src) {
        if (src->shared) {
            use_label = data->file_context;
        } else if (src->readonly) {
            use_label = data->content_context;
        } else if (secdef->imagelabel) {
            use_label = secdef->imagelabel;
        } else {
            return 0;
        }
    } else {
        use_label = data->content_context;
    }


    if (src->type == VIR_STORAGE_TYPE_NVME) {
        const virStorageSourceNVMeDef *nvme = src->nvme;

        if (!(vfioGroupDev = virPCIDeviceAddressGetIOMMUGroupDev(&nvme->pciAddr)))
            return -1;

        path = vfioGroupDev;
    }

    ret = virSecuritySELinuxSetFilecon(mgr, path, use_label, remember);

    if (ret == 1 && !disk_seclabel) {


        disk_seclabel = virSecurityDeviceLabelDefNew(SECURITY_SELINUX_NAME);
        if (!disk_seclabel)
            return -1;
        disk_seclabel->labelskip = true;
        if (VIR_APPEND_ELEMENT(src->seclabels, src->nseclabels,
                               disk_seclabel) < 0) {
            virSecurityDeviceLabelDefFree(disk_seclabel);
            return -1;
        }
        ret = 0;
    }

    return ret;
}
