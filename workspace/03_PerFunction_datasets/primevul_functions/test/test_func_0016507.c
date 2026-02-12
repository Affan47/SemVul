void InstanceKlass::eager_initialize(Thread *thread) {
  if (!EagerInitialization) return;

  if (this->is_not_initialized()) {

    if (this->class_initializer() != NULL) return;


    Klass* super_klass = super();
    if (super_klass == NULL) return;


    if (!InstanceKlass::cast(super_klass)->is_initialized()) return;


    eager_initialize_impl();
  }
}
