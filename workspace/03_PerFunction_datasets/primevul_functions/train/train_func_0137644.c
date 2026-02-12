InstanceKlass* InstanceKlass::nest_host(TRAPS) {
  InstanceKlass* nest_host_k = _nest_host;
  if (nest_host_k != NULL) {
    return nest_host_k;
  }

  ResourceMark rm(THREAD);


  if (_nest_host_index != 0) {

    bool can_resolve = THREAD->can_call_java();
    if (!can_resolve && !_constants->tag_at(_nest_host_index).is_klass()) {
      log_trace(class, nestmates)("Rejected resolution of nest-host of %s in unsuitable thread",
                                  this->external_name());
      return NULL;
    }

    log_trace(class, nestmates)("Resolving nest-host of %s using cp entry for %s",
                                this->external_name(),
                                _constants->klass_name_at(_nest_host_index)->as_C_string());

    Klass* k = _constants->klass_at(_nest_host_index, THREAD);
    if (HAS_PENDING_EXCEPTION) {
      if (PENDING_EXCEPTION->is_a(vmClasses::VirtualMachineError_klass())) {
        return NULL;
      }
      stringStream ss;
      char* target_host_class = _constants->klass_name_at(_nest_host_index)->as_C_string();
      ss.print("Nest host resolution of %s with host %s failed: ",
               this->external_name(), target_host_class);
      java_lang_Throwable::print(PENDING_EXCEPTION, &ss);
      const char* msg = ss.as_string(true );
      constantPoolHandle cph(THREAD, constants());
      SystemDictionary::add_nest_host_error(cph, _nest_host_index, msg);
      CLEAR_PENDING_EXCEPTION;

      log_trace(class, nestmates)("%s", msg);
    } else {


      const char* error = NULL;


      if (is_same_class_package(k)) {


        if (k->is_instance_klass()) {
          nest_host_k = InstanceKlass::cast(k);
          bool is_member = nest_host_k->has_nest_member(THREAD, this);
          if (is_member) {
            _nest_host = nest_host_k;

            log_trace(class, nestmates)("Resolved nest-host of %s to %s",
                                        this->external_name(), k->external_name());
            return nest_host_k;
          } else {
            error = "current type is not listed as a nest member";
          }
        } else {
          error = "host is not an instance class";
        }
      } else {
        error = "types are in different packages";
      }


      {
        stringStream ss;
        ss.print("Type %s (loader: %s) is not a nest member of type %s (loader: %s): %s",
                 this->external_name(),
                 this->class_loader_data()->loader_name_and_id(),
                 k->external_name(),
                 k->class_loader_data()->loader_name_and_id(),
                 error);
        const char* msg = ss.as_string(true );
        constantPoolHandle cph(THREAD, constants());
        SystemDictionary::add_nest_host_error(cph, _nest_host_index, msg);
        log_trace(class, nestmates)("%s", msg);
      }
    }
  } else {
    log_trace(class, nestmates)("Type %s is not part of a nest: setting nest-host to self",
                                this->external_name());
  }


  return (_nest_host = this);
}
