storagePoolUpdateStateCallback(virStoragePoolObj *obj,
                               const void *opaque G_GNUC_UNUSED)
{
    virStoragePoolDef *def = virStoragePoolObjGetDef(obj);
    bool active = false;
    virStorageBackend *backend;
    g_autofree char *stateFile = NULL;

    if ((backend = virStorageBackendForType(def->type)) == NULL) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("Missing backend %d"), def->type);
        return;
    }

    if (!(stateFile = virFileBuildPath(driver->stateDir, def->name, ".xml")))
        return;


    if (backend->checkPool &&
        backend->checkPool(obj, &active) < 0) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("Failed to initialize storage pool '%s': %s"),
                       def->name, virGetLastErrorMessage());
        unlink(stateFile);
        active = false;
    }


    if (active &&
        storagePoolRefreshImpl(backend, obj, stateFile) < 0) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       _("Failed to restart storage pool '%s': %s"),
                       def->name, virGetLastErrorMessage());
        active = false;
    }

    virStoragePoolObjSetActive(obj, active);

    if (!virStoragePoolObjIsActive(obj))
        virStoragePoolUpdateInactive(obj);

    return;
}
