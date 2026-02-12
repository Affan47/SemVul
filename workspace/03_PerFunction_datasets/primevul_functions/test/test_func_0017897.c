void LinkResolver::runtime_resolve_special_method(CallInfo& result,
                                                  const LinkInfo& link_info,
                                                  const methodHandle& resolved_method,
                                                  Handle recv, TRAPS) {

  Klass* resolved_klass = link_info.resolved_klass();


  methodHandle sel_method(THREAD, resolved_method());

  if (link_info.check_access() &&

      resolved_method->name() != vmSymbols::object_initializer_name()) {

    Klass* current_klass = link_info.current_klass();


    if (current_klass->is_subclass_of(resolved_klass) &&
        current_klass != resolved_klass) {

      Klass* super_klass = current_klass->super();
      Method* instance_method = lookup_instance_method_in_klasses(super_klass,
                                                     resolved_method->name(),
                                                     resolved_method->signature(),
                                                     Klass::PrivateLookupMode::find);
      sel_method = methodHandle(THREAD, instance_method);


      if (sel_method.is_null()) {
        ResourceMark rm(THREAD);
        stringStream ss;
        ss.print("'");
        resolved_method->print_external_name(&ss);
        ss.print("'");
        THROW_MSG(vmSymbols::java_lang_AbstractMethodError(), ss.as_string());

      } else if (link_info.check_loader_constraints() && sel_method() != resolved_method()) {
        check_method_loader_constraints(link_info, sel_method, "method", CHECK);
      }
    }


    InstanceKlass* sender = InstanceKlass::cast(current_klass);
    if (sender->is_interface() && recv.not_null()) {
      Klass* receiver_klass = recv->klass();
      if (!receiver_klass->is_subtype_of(sender)) {
        ResourceMark rm(THREAD);
        char buf[500];
        jio_snprintf(buf, sizeof(buf),
                     "Receiver class %s must be the current class or a subtype of interface %s",
                     receiver_klass->external_name(),
                     sender->external_name());
        THROW_MSG(vmSymbols::java_lang_IllegalAccessError(), buf);
      }
    }
  }


  if (sel_method->is_static()) {
    ResourceMark rm(THREAD);
    stringStream ss;
    ss.print("Expecting non-static method '");
    resolved_method->print_external_name(&ss);
    ss.print("'");
    THROW_MSG(vmSymbols::java_lang_IncompatibleClassChangeError(), ss.as_string());
  }


  if (sel_method->is_abstract()) {
    ResourceMark rm(THREAD);
    stringStream ss;
    ss.print("'");
    Method::print_external_name(&ss, resolved_klass, sel_method->name(), sel_method->signature());
    ss.print("'");
    THROW_MSG(vmSymbols::java_lang_AbstractMethodError(), ss.as_string());
  }

  if (log_develop_is_enabled(Trace, itables)) {
    trace_method_resolution("invokespecial selected method: resolved-class:",
                            resolved_klass, resolved_klass, sel_method(), true);
  }


  result.set_static(resolved_klass, sel_method, CHECK);
}
