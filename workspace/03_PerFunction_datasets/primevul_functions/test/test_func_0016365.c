bool InstanceKlass::is_same_package_member(const Klass* class2, TRAPS) const {
  if (class2 == this) return true;
  if (!class2->is_instance_klass())  return false;


  if (!is_same_class_package(class2))
    return false;


  const InstanceKlass* outer_this = this;
  for (;;) {


    bool ignore_inner_is_member;
    const Klass* next = outer_this->compute_enclosing_class(&ignore_inner_is_member,
                                                            CHECK_false);
    if (next == NULL)  break;
    if (next == class2)  return true;
    outer_this = InstanceKlass::cast(next);
  }


  const InstanceKlass* outer2 = InstanceKlass::cast(class2);
  for (;;) {
    bool ignore_inner_is_member;
    Klass* next = outer2->compute_enclosing_class(&ignore_inner_is_member,
                                                    CHECK_false);
    if (next == NULL)  break;

    if (next == this)  return true;
    if (next == outer_this)  return true;
    outer2 = InstanceKlass::cast(next);
  }


  return false;
}
