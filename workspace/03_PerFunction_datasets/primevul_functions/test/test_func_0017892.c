Method* LinkResolver::lookup_method_in_interfaces(const LinkInfo& cp_info) {
  InstanceKlass *ik = InstanceKlass::cast(cp_info.resolved_klass());


  return ik->lookup_method_in_all_interfaces(cp_info.name(), cp_info.signature(), Klass::DefaultsLookupMode::skip);
}
