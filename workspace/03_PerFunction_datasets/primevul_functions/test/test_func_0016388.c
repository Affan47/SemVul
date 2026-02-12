oop InstanceKlass::protection_domain() const {

  return java_lang_Class::protection_domain(java_mirror());
}
