methodHandle LinkResolver::linktime_resolve_special_method(const LinkInfo& link_info,
                                                           TRAPS) {


  Klass* resolved_klass = link_info.resolved_klass();
  methodHandle resolved_method;

  if (!resolved_klass->is_interface()) {
    resolved_method = resolve_method(link_info, Bytecodes::_invokespecial, CHECK_NULL);
  } else {
    resolved_method = resolve_interface_method(link_info, Bytecodes::_invokespecial, CHECK_NULL);
  }


  if (resolved_method->name() == vmSymbols::object_initializer_name() &&
      resolved_method->method_holder() != resolved_klass) {
    ResourceMark rm(THREAD);
    stringStream ss;
    ss.print("%s: method '", resolved_klass->external_name());
    resolved_method->signature()->print_as_signature_external_return_type(&ss);
    ss.print(" %s(", resolved_method->name()->as_C_string());
    resolved_method->signature()->print_as_signature_external_parameters(&ss);
    ss.print(")' not found");
    Exceptions::fthrow(
      THREAD_AND_LOCATION,
      vmSymbols::java_lang_NoSuchMethodError(),
      "%s", ss.as_string());
    return NULL;
  }


  Klass* current_klass = link_info.current_klass();
  if (current_klass != NULL && resolved_klass->is_interface()) {
    InstanceKlass* ck = InstanceKlass::cast(current_klass);
    InstanceKlass *klass_to_check = !ck->is_anonymous() ?
                                    ck :
                                    InstanceKlass::cast(ck->host_klass());

    bool is_reflect = klass_to_check->is_subclass_of(
                        SystemDictionary::reflect_MagicAccessorImpl_klass());

    if (!is_reflect &&
        !klass_to_check->is_same_or_direct_interface(resolved_klass)) {
      ResourceMark rm(THREAD);
      stringStream ss;
      ss.print("Interface method reference: '");
      resolved_method->print_external_name(&ss);
      ss.print("', is in an indirect superinterface of %s",
               current_klass->external_name());
      THROW_MSG_NULL(vmSymbols::java_lang_IncompatibleClassChangeError(), ss.as_string());
    }
  }


  if (resolved_method->is_static()) {
    ResourceMark rm(THREAD);
    stringStream ss;
    ss.print("Expecting non-static method '");
    resolved_method->print_external_name(&ss);
    ss.print("'");
    THROW_MSG_NULL(vmSymbols::java_lang_IncompatibleClassChangeError(), ss.as_string());
  }

  if (log_develop_is_enabled(Trace, itables)) {
    trace_method_resolution("invokespecial resolved method: caller-class:",
                            current_klass, resolved_klass, resolved_method, true);
  }

  return resolved_method;
}
