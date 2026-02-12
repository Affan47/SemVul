void InstanceKlass::initialize_super_interfaces(TRAPS) {
  assert (has_nonstatic_concrete_methods(), "caller should have checked this");
  for (int i = 0; i < local_interfaces()->length(); ++i) {
    Klass* iface = local_interfaces()->at(i);
    InstanceKlass* ik = InstanceKlass::cast(iface);


    if (ik->has_nonstatic_concrete_methods()) {
      ik->initialize_super_interfaces(CHECK);
    }


    if (ik->should_be_initialized() && ik->declares_nonstatic_concrete_methods()) {
      ik->initialize(CHECK);
    }
  }
}
