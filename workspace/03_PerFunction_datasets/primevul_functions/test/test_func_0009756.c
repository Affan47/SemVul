CallInfo::CallInfo(Method* resolved_method, Klass* resolved_klass, TRAPS) {
  Klass* resolved_method_holder = resolved_method->method_holder();
  if (resolved_klass == NULL) {
    resolved_klass = resolved_method_holder;
  }
  _resolved_klass  = resolved_klass;
  _selected_klass  = resolved_klass;
  _resolved_method = resolved_method;
  _selected_method = resolved_method;

  CallKind kind = CallInfo::unknown_kind;
  int index = resolved_method->vtable_index();
  if (resolved_method->can_be_statically_bound()) {
    kind = CallInfo::direct_call;
  } else if (!resolved_method_holder->is_interface()) {

    kind = CallInfo::vtable_call;
  } else if (!resolved_klass->is_interface()) {

    index = LinkResolver::vtable_index_of_interface_method(resolved_klass,
                           resolved_method);
    assert(index >= 0 , "we should have valid vtable index at this point");

    kind = CallInfo::vtable_call;
  } else if (resolved_method->has_vtable_index()) {


#ifdef ASSERT

    Klass* object_klass = SystemDictionary::Object_klass();
    Method * object_resolved_method = object_klass->vtable().method_at(index);
    assert(object_resolved_method->name() == resolved_method->name(),
      "Object and interface method names should match at vtable index %d, %s != %s",
      index, object_resolved_method->name()->as_C_string(), resolved_method->name()->as_C_string());
    assert(object_resolved_method->signature() == resolved_method->signature(),
      "Object and interface method signatures should match at vtable index %d, %s != %s",
      index, object_resolved_method->signature()->as_C_string(), resolved_method->signature()->as_C_string());
#endif

    kind = CallInfo::vtable_call;
  } else {

    kind = CallInfo::itable_call;
    index = resolved_method->itable_index();
  }
  assert(index == Method::nonvirtual_vtable_index || index >= 0, "bad index %d", index);
  _call_kind  = kind;
  _call_index = index;
  _resolved_appendix = Handle();

  set_resolved_method_name(CHECK);

  DEBUG_ONLY(verify());
}
