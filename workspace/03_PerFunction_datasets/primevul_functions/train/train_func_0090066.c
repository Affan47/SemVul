RecordADeviceEvent(CallbackListPtr *pcbl, void *nulldata, void *calldata)
{
    DeviceEventInfoRec *pei = (DeviceEventInfoRec *) calldata;
    RecordContextPtr pContext;
    RecordClientsAndProtocolPtr pRCAP;
    int eci;

    for (eci = 0; eci < numEnabledContexts; eci++) {
        pContext = ppAllContexts[eci];
        for (pRCAP = pContext->pListOfRCAP; pRCAP; pRCAP = pRCAP->pNextRCAP) {
            if (pRCAP->pDeviceEventSet) {
                int count;
                xEvent *xi_events = NULL;


                if (IsMaster(pei->device)) {
                    xEvent *core_events;

                    EventToCore(pei->event, &core_events, &count);
                    RecordSendProtocolEvents(pRCAP, pContext, core_events,
                                             count);
                    free(core_events);
                }

                EventToXI(pei->event, &xi_events, &count);
                RecordSendProtocolEvents(pRCAP, pContext, xi_events, count);
                free(xi_events);
            }
        }
    }
}
