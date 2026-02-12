RecordDeleteContext(void *value, XID id)
{
    int i;
    RecordContextPtr pContext = (RecordContextPtr) value;
    RecordClientsAndProtocolPtr pRCAP;

    RecordDisableContext(pContext);


    while ((pRCAP = pContext->pListOfRCAP)) {
        int numClients = pRCAP->numClients;


        while (numClients--) {
            RecordDeleteClientFromRCAP(pRCAP, numClients);
        }
    }


    if (-1 != (i = RecordFindContextOnAllContexts(pContext))) {
        ppAllContexts[i] = ppAllContexts[numContexts - 1];
        if (--numContexts == 0) {
            free(ppAllContexts);
            ppAllContexts = NULL;
        }
    }
    free(pContext);

    return Success;
}
