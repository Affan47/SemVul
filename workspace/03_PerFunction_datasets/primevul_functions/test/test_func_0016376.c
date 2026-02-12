jint InstanceKlass::compute_modifier_flags(TRAPS) const {
  jint access = access_flags().as_int();


  InnerClassesIterator iter(this);
  for (; !iter.done(); iter.next()) {
    int ioff = iter.inner_class_info_index();


    if (ioff == 0) continue;


    Symbol* inner_name = constants()->klass_name_at(ioff);
    if (name() == inner_name) {

      access = iter.inner_access_flags();
      break;
    }
  }

  return (access & (~JVM_ACC_SUPER)) & JVM_ACC_WRITTEN_FLAGS;
}
