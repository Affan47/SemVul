storeFsSetup_ufs(storefs_entry_t * storefs)
{
    assert(!ufs_initialised);
    storefs->parsefunc = storeUfsDirParse;
    storefs->reconfigurefunc = storeUfsDirReconfigure;
    storefs->donefunc = storeUfsDirDone;
    ufs_state_pool = memPoolCreate("UFS IO State data", sizeof(ufsstate_t));
    ufs_initialised = 1;
}
