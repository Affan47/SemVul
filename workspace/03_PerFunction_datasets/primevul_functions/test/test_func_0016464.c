InstanceKlass* InstanceKlass::nest_host(Symbol* validationException, TRAPS) {
  InstanceKlass* nest_host_k = _nest_host;
  if (nest_host_k == NULL) {


    if (_nest_host_index != 0) {

      if (!THREAD->can_call_java() && !_constants->tag_at(_nest_host_index).is_klass()) {
        if (log_is_enabled(Trace, class, nestmates)) {
          ResourceMark rm(THREAD);
          log_trace(class, nestmates)("Rejected resolution of nest-host of %s in unsuitable thread",
                                      this->external_name());
        }
        return NULL;
      }

      if (log_is_enabled(Trace, class, nestmates)) {
        ResourceMark rm(THREAD);
        log_trace(class, nestmates)("Resolving nest-host of %s using cp entry for %s",
                                    this->external_name(),
                                    _constants->klass_name_at(_nest_host_index)->as_C_string());
      }

      Klass* k = _constants->klass_at(_nest_host_index, THREAD);
      if (HAS_PENDING_EXCEPTION) {
        Handle exc_h = Handle(THREAD, PENDING_EXCEPTION);
        if (exc_h->is_a(SystemDictionary::NoClassDefFoundError_klass())) {

          ResourceMark rm(THREAD);
          char buf[200];
          CLEAR_PENDING_EXCEPTION;
          jio_snprintf(buf, sizeof(buf),
                       "Unable to load nest-host class (%s) of %s",
                       _constants->klass_name_at(_nest_host_index)->as_C_string(),
                       this->external_name());
          log_trace(class, nestmates)("%s - NoClassDefFoundError", buf);
          THROW_MSG_CAUSE_NULL(vmSymbols::java_lang_NoClassDefFoundError(), buf, exc_h);
        }

        return NULL;
      }


      const char* error = NULL;


      if (is_same_class_package(k)) {


        if (k->is_instance_klass()) {
          nest_host_k = InstanceKlass::cast(k);

          bool is_member = nest_host_k->has_nest_member(this, CHECK_NULL);
          if (is_member) {

            _nest_host = nest_host_k;

            if (log_is_enabled(Trace, class, nestmates)) {
              ResourceMark rm(THREAD);
              log_trace(class, nestmates)("Resolved nest-host of %s to %s",
                                          this->external_name(), k->external_name());
            }
            return nest_host_k;
          }
        }
        error = "current type is not listed as a nest member";
      } else {
        error = "types are in different packages";
      }

      if (log_is_enabled(Trace, class, nestmates)) {
        ResourceMark rm(THREAD);
        log_trace(class, nestmates)("Type %s is not a nest member of resolved type %s: %s",
                                    this->external_name(),
                                    k->external_name(),
                                    error);
      }

      if (validationException != NULL && THREAD->can_call_java()) {
        ResourceMark rm(THREAD);
        Exceptions::fthrow(THREAD_AND_LOCATION,
                           validationException,
                           "Type %s is not a nest member of %s: %s",
                           this->external_name(),
                           k->external_name(),
                           error
                           );
      }
      return NULL;
    } else {
      if (log_is_enabled(Trace, class, nestmates)) {
        ResourceMark rm(THREAD);
        log_trace(class, nestmates)("Type %s is not part of a nest: setting nest-host to self",
                                    this->external_name());
      }

      return (_nest_host = this);
    }
  }
  return nest_host_k;
}
