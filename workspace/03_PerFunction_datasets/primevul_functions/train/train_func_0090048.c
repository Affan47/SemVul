RecordFlushAllContexts(CallbackListPtr *pcbl,
                       void *nulldata, void *calldata)
{
    int eci;
    RecordContextPtr pContext;

    for (eci = 0; eci < numEnabledContexts; eci++) {
        pContext = ppAllContexts[eci];


        if (pContext->numBufBytes)
            RecordFlushReplyBuffer(ppAllContexts[eci], NULL, 0, NULL, 0);
    }
}
