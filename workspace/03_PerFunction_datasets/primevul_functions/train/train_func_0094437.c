event_handler(int, void *)
  {
    EThread *eth = this_ethread();

    MUTEX_TRY_LOCK(lock, _target->mutex, eth);
    if (lock.is_locked()) {
      _target->handleEvent(_eventId, _edata);
      delete this;
    } else {
      eventProcessor.schedule_imm(this, ET_NET);
    }
    return 0;
  }
