ZrtpStateClass::~ZrtpStateClass(void) {


    if (!inState(Initial)) {
        Event_t ev;

        cancelTimer();
        ev.type = ZrtpClose;
        event = &ev;
        engine->processEvent(*this);
    }
    delete engine;
}
