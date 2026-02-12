ContWrapper(ProxyMutex *mutex,
              Continuation *target,
              int eventId = EVENT_IMMEDIATE,
              void *edata = nullptr
              )
    : Continuation(mutex), _target(target), _eventId(eventId), _edata(edata)
  {
    SET_HANDLER(&ContWrapper::event_handler);
  }
