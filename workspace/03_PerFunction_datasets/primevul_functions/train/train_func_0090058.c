RecordSendProtocolEvents(RecordClientsAndProtocolPtr pRCAP,
                         RecordContextPtr pContext, xEvent *pev, int count)
{
    int ev;

    for (ev = 0; ev < count; ev++, pev++) {
        if (RecordIsMemberOfSet(pRCAP->pDeviceEventSet, pev->u.u.type & 0177)) {
            xEvent swappedEvent;
            xEvent *pEvToRecord = pev;

#ifdef PANORAMIX
            xEvent shiftedEvent;

            if (!noPanoramiXExtension &&
                (pev->u.u.type == MotionNotify ||
                 pev->u.u.type == ButtonPress ||
                 pev->u.u.type == ButtonRelease ||
                 pev->u.u.type == KeyPress || pev->u.u.type == KeyRelease)) {
                int scr = XineramaGetCursorScreen(inputInfo.pointer);

                memcpy(&shiftedEvent, pev, sizeof(xEvent));
                shiftedEvent.u.keyButtonPointer.rootX +=
                    screenInfo.screens[scr]->x - screenInfo.screens[0]->x;
                shiftedEvent.u.keyButtonPointer.rootY +=
                    screenInfo.screens[scr]->y - screenInfo.screens[0]->y;
                pEvToRecord = &shiftedEvent;
            }
#endif

            if (pContext->pRecordingClient->swapped) {
                (*EventSwapVector[pEvToRecord->u.u.type & 0177])
                    (pEvToRecord, &swappedEvent);
                pEvToRecord = &swappedEvent;
            }

            RecordAProtocolElement(pContext, NULL,
                                   XRecordFromServer, pEvToRecord,
                                   SIZEOF(xEvent), 0, 0);


            SetCriticalOutputPending();
        }
    }

}
