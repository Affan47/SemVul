CRMF_CreateCertRequest (PRUint32 inRequestID)
{
    PLArenaPool     *poolp;
    CRMFCertRequest *certReq;
    SECStatus        rv;

    poolp = PORT_NewArena(CRMF_DEFAULT_ARENA_SIZE);
    if (poolp == NULL) {
        goto loser;
    }

    certReq=PORT_ArenaZNew(poolp,CRMFCertRequest);
    if (certReq == NULL) {
        goto loser;
    }

    certReq->poolp = poolp;
    certReq->requestID = inRequestID;

    rv = crmf_encode_unsigned_integer(poolp, &(certReq->certReqId),
                                      inRequestID);
    if (rv != SECSuccess) {
        goto loser;
    }

    return certReq;
 loser:
    if (poolp) {
        PORT_FreeArena(poolp, PR_FALSE);
    }
    return NULL;
}
