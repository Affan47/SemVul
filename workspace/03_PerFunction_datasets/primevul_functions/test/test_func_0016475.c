oop InstanceKlass::init_lock() const {

  oop lock = java_lang_Class::init_lock(java_mirror());

  OrderAccess::loadload();
  assert((oop)lock != NULL || !is_not_initialized(),
         "only fully initialized state can have a null lock");
  return lock;
}
