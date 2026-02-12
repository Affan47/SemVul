void InstanceKlass::fence_and_clear_init_lock() {

  OrderAccess::storestore();
  java_lang_Class::set_init_lock(java_mirror(), NULL);
  assert(!is_not_initialized(), "class must be initialized now");
}
