ensRegistryGetMarkerfeatureadaptor(
    EnsPDatabaseadaptor dba)
{
    RegistryPEntry entry   = NULL;
    RegistryPCoreStyle rcs = NULL;

    if (!dba)
        return NULL;

    entry = (RegistryPEntry) ajTableFetchmodV(
        registryGEntry,
        (const void *) ensDatabaseadaptorGetSpecies(dba));

    if (!entry)
        return NULL;

    switch (ensDatabaseadaptorGetGroup(dba))
    {
        case ensEDatabaseadaptorGroupCore:

        case ensEDatabaseadaptorGroupVega:

        case ensEDatabaseadaptorGroupOtherFeatures:

        case ensEDatabaseadaptorGroupCopyDNA:

            rcs = (RegistryPCoreStyle)
                entry->Registry[ensDatabaseadaptorGetGroup(dba)];

            if (!rcs)
                break;

            if (!rcs->Markerfeatureadaptor)
                rcs->Markerfeatureadaptor =
                    ensMarkerfeatureadaptorNew(dba);

            return rcs->Markerfeatureadaptor;

            break;

        default:

            ajWarn("ensRegistryGetMarkerfeatureadaptor got an "
                   "Ensembl Database Adaptor "
                   "with an unexpected group %d.\n",
                   ensDatabaseadaptorGetGroup(dba));
    }

    return NULL;
}
