wrap(ProxyMutex *mutex,
       Continuation *target,
       int eventId = EVENT_IMMEDIATE,
       void *edata = nullptr
  )
  {
    EThread *eth = this_ethread();
    if (!target->mutex) {

      target->handleEvent(eventId, edata);
    } else {
      MUTEX_TRY_LOCK(lock, target->mutex, eth);
      if (lock.is_locked()) {
        target->handleEvent(eventId, edata);
      } else {
        eventProcessor.schedule_imm(new ContWrapper(mutex, target, eventId, edata), ET_NET);
      }
    }
  }
