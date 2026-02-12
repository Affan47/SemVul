RecordDeleteClientFromRCAP(RecordClientsAndProtocolPtr pRCAP, int position)
{
    if (pRCAP->pContext->pRecordingClient)
        RecordUninstallHooks(pRCAP, pRCAP->pClientIDs[position]);
    if (position != pRCAP->numClients - 1)
        pRCAP->pClientIDs[position] = pRCAP->pClientIDs[pRCAP->numClients - 1];
    if (--pRCAP->numClients == 0) {
        RecordContextPtr pContext = pRCAP->pContext;

        if (pContext->pRecordingClient)
            RecordUninstallHooks(pRCAP, 0);
        if (pContext->pListOfRCAP == pRCAP)
            pContext->pListOfRCAP = pRCAP->pNextRCAP;
        else {
            RecordClientsAndProtocolPtr prevRCAP;

            for (prevRCAP = pContext->pListOfRCAP;
                 prevRCAP->pNextRCAP != pRCAP; prevRCAP = prevRCAP->pNextRCAP);
            prevRCAP->pNextRCAP = pRCAP->pNextRCAP;
        }

        if (pRCAP->clientIDsSeparatelyAllocated)
            free(pRCAP->pClientIDs);
        free(pRCAP);
    }
}
