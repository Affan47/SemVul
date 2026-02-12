RecordDisableContext(RecordContextPtr pContext)
{
    RecordClientsAndProtocolPtr pRCAP;
    int i;

    if (!pContext->pRecordingClient)
        return;
    if (!pContext->pRecordingClient->clientGone) {
        RecordAProtocolElement(pContext, NULL, XRecordEndOfData, NULL, 0, 0, 0);
        RecordFlushReplyBuffer(pContext, NULL, 0, NULL, 0);
    }

    AttendClient(pContext->pRecordingClient);

    for (pRCAP = pContext->pListOfRCAP; pRCAP; pRCAP = pRCAP->pNextRCAP) {
        RecordUninstallHooks(pRCAP, 0);
    }

    pContext->pRecordingClient = NULL;


    i = RecordFindContextOnAllContexts(pContext);
    assert(i != -1);
    assert(i < numEnabledContexts);
    if (i != (numEnabledContexts - 1)) {
        ppAllContexts[i] = ppAllContexts[numEnabledContexts - 1];
        ppAllContexts[numEnabledContexts - 1] = pContext;
    }
    --numEnabledContexts;
    assert(numEnabledContexts >= 0);
}
