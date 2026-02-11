SECMOD_IsModulePresent( unsigned long int pubCipherEnableFlags )
{
    PRBool result = PR_FALSE;
    SECMODModuleList *mods;

    if (!moduleLock) {
    	PORT_SetError(SEC_ERROR_NOT_INITIALIZED);
	return result;
    }
    SECMOD_GetReadLock(moduleLock);
    mods = SECMOD_GetDefaultModuleList();
    for ( ; mods != NULL; mods = mods->next) {
        if (mods->module->ssl[0] &
		SECMOD_PubCipherFlagstoInternal(pubCipherEnableFlags)) {
            result = PR_TRUE;
        }
    }

    SECMOD_ReleaseReadLock(moduleLock);
    return result;
}
