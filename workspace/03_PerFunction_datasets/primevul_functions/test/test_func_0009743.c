void CallInfo::set_interface(Klass* resolved_klass,
                             Klass* selected_klass,
                             const methodHandle& resolved_method,
                             const methodHandle& selected_method,
                             int itable_index, TRAPS) {


  assert(resolved_method->method_holder()->is_interface(), "");
  assert(itable_index == resolved_method()->itable_index(), "");
  set_common(resolved_klass, selected_klass, resolved_method, selected_method, CallInfo::itable_call, itable_index, CHECK);
}
