bool InstanceKlass::has_nest_member(InstanceKlass* k, TRAPS) const {
  if (_nest_members == NULL || _nest_members == Universe::the_empty_short_array()) {
    if (log_is_enabled(Trace, class, nestmates)) {
      ResourceMark rm(THREAD);
      log_trace(class, nestmates)("Checked nest membership of %s in non-nest-host class %s",
                                  k->external_name(), this->external_name());
    }
    return false;
  }

  if (log_is_enabled(Trace, class, nestmates)) {
    ResourceMark rm(THREAD);
    log_trace(class, nestmates)("Checking nest membership of %s in %s",
                                k->external_name(), this->external_name());
  }


  for (int i = 0; i < _nest_members->length(); i++) {
    int cp_index = _nest_members->at(i);
    Symbol* name = _constants->klass_name_at(cp_index);
    if (name == k->name()) {
      log_trace(class, nestmates)("- Found it at nest_members[%d] => cp[%d]", i, cp_index);


      if (!THREAD->can_call_java() && !_constants->tag_at(cp_index).is_klass()) {
        log_trace(class, nestmates)("- validation required resolution in an unsuitable thread");
        return false;
      }

      Klass* k2 = _constants->klass_at(cp_index, CHECK_false);
      if (k2 == k) {
        log_trace(class, nestmates)("- class is listed as a nest member");
        return true;
      } else {

        log_trace(class, nestmates)(" - klass comparison failed!");

        return false;
      }
    }
  }
  log_trace(class, nestmates)("- class is NOT a nest member!");
  return false;
}
