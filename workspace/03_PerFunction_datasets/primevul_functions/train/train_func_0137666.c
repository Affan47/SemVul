Klass* InstanceKlass::array_klass(int n, TRAPS) {

  if (array_klasses_acquire() == NULL) {
    ResourceMark rm(THREAD);
    JavaThread *jt = THREAD;
    {

      MutexLocker ma(THREAD, MultiArray_lock);


      if (array_klasses() == NULL) {
        ObjArrayKlass* k = ObjArrayKlass::allocate_objArray_klass(class_loader_data(), 1, this, CHECK_NULL);

        release_set_array_klasses(k);
      }
    }
  }

  ObjArrayKlass* oak = array_klasses();
  return oak->array_klass(n, THREAD);
}
