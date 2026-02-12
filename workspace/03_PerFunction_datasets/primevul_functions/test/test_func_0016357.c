void InstanceKlass::remove_java_mirror() {
  Klass::remove_java_mirror();


  if (array_klasses() != NULL) {
    array_klasses()->remove_java_mirror();
  }
}
