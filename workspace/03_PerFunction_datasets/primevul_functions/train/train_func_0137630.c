void InstanceKlass::add_implementor(InstanceKlass* ik) {
  if (Universe::is_fully_initialized()) {
    assert_lock_strong(Compile_lock);
  }
  assert(is_interface(), "not interface");


  if (ik->is_interface()) return;


  InstanceKlass* super_ik = ik->java_super();
  if (super_ik != NULL && super_ik->implements_interface(this))


    return;

  InstanceKlass* iklass = implementor();
  if (iklass == NULL) {
    set_implementor(ik);
  } else if (iklass != this && iklass != ik) {


    set_implementor(this);
  }


  for (int index = 0; index < local_interfaces()->length(); index++) {
    local_interfaces()->at(index)->add_implementor(ik);
  }
}
