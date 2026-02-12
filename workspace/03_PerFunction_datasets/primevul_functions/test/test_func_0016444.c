bool InstanceKlass::is_same_class_package(const Klass* class2) const {
  oop classloader1 = this->class_loader();
  PackageEntry* classpkg1 = this->package();
  if (class2->is_objArray_klass()) {
    class2 = ObjArrayKlass::cast(class2)->bottom_klass();
  }

  oop classloader2;
  PackageEntry* classpkg2;
  if (class2->is_instance_klass()) {
    classloader2 = class2->class_loader();
    classpkg2 = class2->package();
  } else {
    assert(class2->is_typeArray_klass(), "should be type array");
    classloader2 = NULL;
    classpkg2 = NULL;
  }


  if ((classloader1 == classloader2) && (classpkg1 == classpkg2)) {
    return true;
  }

  return false;
}
