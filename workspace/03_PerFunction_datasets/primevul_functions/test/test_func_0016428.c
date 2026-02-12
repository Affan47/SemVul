Klass* InstanceKlass::array_klass_impl(bool or_null, int n, TRAPS) {

  if (array_klasses_acquire() == NULL) {
    if (or_null) return NULL;

    ResourceMark rm;
    JavaThread *jt = (JavaThread *)THREAD;
    {

      MutexLocker mc(Compile_lock, THREAD);
      MutexLocker ma(MultiArray_lock, THREAD);


      if (array_klasses() == NULL) {
        Klass*    k = ObjArrayKlass::allocate_objArray_klass(class_loader_data(), 1, this, CHECK_NULL);

        release_set_array_klasses(k);
      }
    }
  }

  ObjArrayKlass* oak = (ObjArrayKlass*)array_klasses();
  if (or_null) {
    return oak->array_klass_or_null(n);
  }
  return oak->array_klass(n, THREAD);
}
