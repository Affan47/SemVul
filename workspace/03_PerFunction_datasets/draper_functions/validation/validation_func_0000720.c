schedule(Aword event, Aword where, Aword after)
{
    int i;

    if (event == 0) syserr("NULL event");

    cancelEvent(event);

    if (eventQueue == NULL || eventQueueTop == eventQueueSize)
        increaseEventQueue();


    for (i = eventQueueTop; i >= 1 && eventQueue[i-1].after <= after; i--) {
        eventQueue[i].event = eventQueue[i-1].event;
        eventQueue[i].after = eventQueue[i-1].after;
        eventQueue[i].where = eventQueue[i-1].where;
    }

    eventQueue[i].after = after;
    eventQueue[i].where = where;
    eventQueue[i].event = event;
    eventQueueTop++;
}
