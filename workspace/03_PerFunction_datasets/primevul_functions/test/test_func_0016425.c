void InstanceKlass::process_interfaces(Thread *thread) {

  for (int i = local_interfaces()->length() - 1; i >= 0; i--) {
    assert(local_interfaces()->at(i)->is_klass(), "must be a klass");
    InstanceKlass* interf = InstanceKlass::cast(local_interfaces()->at(i));
    assert(interf->is_interface(), "expected interface");
    interf->add_implementor(this);
  }
}
