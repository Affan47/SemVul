void InstanceKlass::eager_initialize_impl() {
  EXCEPTION_MARK;
  HandleMark hm(THREAD);
  Handle h_init_lock(THREAD, init_lock());
  ObjectLocker ol(h_init_lock, THREAD);


  if (!is_not_initialized()) return;

  ClassState old_state = init_state();
  link_class_impl(THREAD);
  if (HAS_PENDING_EXCEPTION) {
    CLEAR_PENDING_EXCEPTION;


    if (old_state != _init_state)
      set_init_state(old_state);
  } else {

    set_init_state(fully_initialized);
    fence_and_clear_init_lock();

    if (log_is_enabled(Info, class, init)) {
      ResourceMark rm(THREAD);
      log_info(class, init)("[Initialized %s without side effects]", external_name());
    }
  }
}
