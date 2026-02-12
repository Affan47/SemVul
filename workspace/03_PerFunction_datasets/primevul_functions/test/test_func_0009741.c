void LinkResolver::resolve_static_call(CallInfo& result,
                                       const LinkInfo& link_info,
                                       bool initialize_class, TRAPS) {
  methodHandle resolved_method = linktime_resolve_static_method(link_info, CHECK);


  Klass* resolved_klass = resolved_method->method_holder();


  if (initialize_class && resolved_klass->should_be_initialized()) {
    resolved_klass->initialize(CHECK);

    LinkInfo new_info(resolved_klass, link_info.name(), link_info.signature(),
                      link_info.current_klass(),
                      link_info.check_access() ? LinkInfo::needs_access_check : LinkInfo::skip_access_check);
    resolved_method = linktime_resolve_static_method(new_info, CHECK);
  }


  result.set_static(resolved_klass, resolved_method, CHECK);
}
