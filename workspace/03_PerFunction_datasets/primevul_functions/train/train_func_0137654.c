void InstanceKlass::clean_implementors_list() {
  assert(is_loader_alive(), "this klass should be live");
  if (is_interface()) {
    assert (ClassUnloading, "only called for ClassUnloading");
    for (;;) {

      InstanceKlass* impl = Atomic::load_acquire(adr_implementor());
      if (impl != NULL && !impl->is_loader_alive()) {

        InstanceKlass* volatile* iklass = adr_implementor();
        if (Atomic::cmpxchg(iklass, impl, (InstanceKlass*)NULL) == impl) {

          if (log_is_enabled(Trace, class, unload)) {
            ResourceMark rm;
            log_trace(class, unload)("unlinking class (implementor): %s", impl->external_name());
          }
          return;
        }
      } else {
        return;
      }
    }
  }
}
