setCommonICUData(UDataMemory *pData,
                 UDataMemory *oldData,

                 UBool       warn,

                 UErrorCode *pErr)
{
    UDataMemory  *newCommonData = UDataMemory_createNewInstance(pErr);
    if (U_FAILURE(*pErr)) {
        return;
    }


    UDatamemory_assign(newCommonData, pData);
    umtx_lock(NULL);
    if (gCommonICUData==oldData) {
        gStubICUData   = gCommonICUData;
        gCommonICUData = newCommonData;
        ucln_common_registerCleanup(UCLN_COMMON_UDATA, udata_cleanup);
    }
    else {
        if  (warn==TRUE) {
            *pErr = U_USING_DEFAULT_WARNING;
        }
        uprv_free(newCommonData);
    }
    umtx_unlock(NULL);
}
