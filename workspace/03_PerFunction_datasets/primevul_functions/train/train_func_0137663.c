InstanceKlass* InstanceKlass::compute_enclosing_class(bool* inner_is_member, TRAPS) const {
  InstanceKlass* outer_klass = NULL;
  *inner_is_member = false;
  int ooff = 0, noff = 0;
  bool has_inner_classes_attr = find_inner_classes_attr(&ooff, &noff, THREAD);
  if (has_inner_classes_attr) {
    constantPoolHandle i_cp(THREAD, constants());
    if (ooff != 0) {
      Klass* ok = i_cp->klass_at(ooff, CHECK_NULL);
      if (!ok->is_instance_klass()) {


        ResourceMark rm(THREAD);
        Exceptions::fthrow(
          THREAD_AND_LOCATION,
          vmSymbols::java_lang_IncompatibleClassChangeError(),
          "%s and %s disagree on InnerClasses attribute",
          ok->external_name(),
          external_name());
        return NULL;
      }
      outer_klass = InstanceKlass::cast(ok);
      *inner_is_member = true;
    }
    if (NULL == outer_klass) {

      int encl_method_class_idx = enclosing_method_class_index();
      if (encl_method_class_idx != 0) {
        Klass* ok = i_cp->klass_at(encl_method_class_idx, CHECK_NULL);
        outer_klass = InstanceKlass::cast(ok);
        *inner_is_member = false;
      }
    }
  }


  if (NULL == outer_klass) return NULL;


  Reflection::check_for_inner_class(outer_klass, this, *inner_is_member, CHECK_NULL);
  return outer_klass;
}
