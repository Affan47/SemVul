void InstanceKlass::methods_do(void f(Method* method)) {


  if (!is_loaded()) {
    return;
  }

  int len = methods()->length();
  for (int index = 0; index < len; index++) {
    Method* m = methods()->at(index);
    assert(m->is_method(), "must be method");
    f(m);
  }
}
