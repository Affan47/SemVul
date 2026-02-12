bool InstanceKlass::find_inner_classes_attr(int* ooff, int* noff, TRAPS) const {
  constantPoolHandle i_cp(THREAD, constants());
  for (InnerClassesIterator iter(this); !iter.done(); iter.next()) {
    int ioff = iter.inner_class_info_index();
    if (ioff != 0) {


      if (i_cp->klass_name_at_matches(this, ioff)) {
        Klass* inner_klass = i_cp->klass_at(ioff, CHECK_false);
        if (this == inner_klass) {
          *ooff = iter.outer_class_info_index();
          *noff = iter.inner_name_index();
          return true;
        }
      }
    }
  }
  return false;
}
