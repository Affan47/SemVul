objArrayOop InstanceKlass::signers() const {

  return java_lang_Class::signers(java_mirror());
}
