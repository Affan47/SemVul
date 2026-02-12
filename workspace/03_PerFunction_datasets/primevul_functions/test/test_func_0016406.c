void InstanceKlass::add_implementor(Klass* k) {
  assert_lock_strong(Compile_lock);
  assert(is_interface(), "not interface");


  if (InstanceKlass::cast(k)->is_interface()) return;


  Klass* sk = k->super();
  if (sk != NULL && InstanceKlass::cast(sk)->implements_interface(this))


    return;

  Klass* ik = implementor();
  if (ik == NULL) {
    set_implementor(k);
  } else if (ik != this && ik != k) {


    set_implementor(this);
  }


  for (int index = 0; index < local_interfaces()->length(); index++) {
    InstanceKlass::cast(local_interfaces()->at(index))->add_implementor(k);
  }
}
