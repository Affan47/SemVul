ProcRecordEnableContext(ClientPtr client)
{
    RecordContextPtr pContext;

    REQUEST(xRecordEnableContextReq);
    int i;
    RecordClientsAndProtocolPtr pRCAP;

    REQUEST_SIZE_MATCH(xRecordGetContextReq);
    VERIFY_CONTEXT(pContext, stuff->context, client);
    if (pContext->pRecordingClient)
        return BadMatch;


    for (pRCAP = pContext->pListOfRCAP; pRCAP; pRCAP = pRCAP->pNextRCAP) {
        int err = RecordInstallHooks(pRCAP, 0);

        if (err != Success) {
            RecordClientsAndProtocolPtr pUninstallRCAP;

            for (pUninstallRCAP = pContext->pListOfRCAP;
                 pUninstallRCAP != pRCAP;
                 pUninstallRCAP = pUninstallRCAP->pNextRCAP) {
                RecordUninstallHooks(pUninstallRCAP, 0);
            }
            return err;
        }
    }


    IgnoreClient(client);
    pContext->pRecordingClient = client;


    RecordDeleteClientFromContext(pContext,
                                  pContext->pRecordingClient->clientAsMask);


    i = RecordFindContextOnAllContexts(pContext);
    assert(i >= numEnabledContexts);
    if (i != numEnabledContexts) {
        ppAllContexts[i] = ppAllContexts[numEnabledContexts];
        ppAllContexts[numEnabledContexts] = pContext;
    }

    ++numEnabledContexts;
    assert(numEnabledContexts > 0);


    RecordAProtocolElement(pContext, NULL, XRecordStartOfData, NULL, 0, 0, 0);
    RecordFlushReplyBuffer(pContext, NULL, 0, NULL, 0);
    return Success;
}
