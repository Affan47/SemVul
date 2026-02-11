nss_Shutdown(void)
{
    SECStatus shutdownRV = SECSuccess;
    SECStatus rv;
    PRStatus status;
    NSSInitContext *temp;

    rv = nss_ShutdownShutdownList();
    if (rv != SECSuccess) {
	shutdownRV = SECFailure;
    }
    cert_DestroyLocks();
    ShutdownCRLCache();
    OCSP_ShutdownGlobal();
    PKIX_Shutdown(plContext);
    SECOID_Shutdown();
    status = STAN_Shutdown();
    cert_DestroySubjectKeyIDHashTable();
    pk11_SetInternalKeySlot(NULL);
    rv = SECMOD_Shutdown();
    if (rv != SECSuccess) {
	shutdownRV = SECFailure;
    }
    pk11sdr_Shutdown();


    nss_DestroyErrorStack();
    nssArena_Shutdown();
    if (status == PR_FAILURE) {
	if (NSS_GetError() == NSS_ERROR_BUSY) {
	    PORT_SetError(SEC_ERROR_BUSY);
	}
	shutdownRV = SECFailure;
    }
    nssIsInitted = PR_FALSE;
    temp = nssInitContextList;
    nssInitContextList = NULL;


    while (temp) {
	NSSInitContext *next = temp->next;
	temp->magic = 0;
	PORT_Free(temp);
	temp = next;
    }
    return shutdownRV;
}
