nwfilterStateReload(void)
{
    if (!driver)
        return -1;

    if (!driver->privileged)
        return 0;

    virNWFilterDHCPSnoopEnd(NULL);

    virNWFilterLearnThreadsTerminate(true);

    nwfilterDriverLock();
    virNWFilterWriteLockFilterUpdates();

    virNWFilterObjListLoadAllConfigs(driver->nwfilters, driver->configDir);

    virNWFilterUnlockFilterUpdates();

    virNWFilterBuildAll(driver, false);

    nwfilterDriverUnlock();

    return 0;
}
