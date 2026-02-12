storageVolDeleteInternal(virStorageBackend *backend,
                         virStoragePoolObj *obj,
                         virStorageVolDef *voldef,
                         unsigned int flags,
                         bool updateMeta)
{
    virStoragePoolDef *def = virStoragePoolObjGetDef(obj);

    if (!backend->deleteVol) {
        virReportError(VIR_ERR_NO_SUPPORT,
                       "%s", _("storage pool does not support vol deletion"));

        return -1;
    }

    if (backend->deleteVol(obj, voldef, flags) < 0)
        return -1;


    if (def->type == VIR_STORAGE_POOL_DISK)
        return 0;


    if (updateMeta) {
        def->allocation -= voldef->target.allocation;
        def->available += voldef->target.allocation;
    }

    virStoragePoolObjRemoveVol(obj, voldef);

    return 0;
}
