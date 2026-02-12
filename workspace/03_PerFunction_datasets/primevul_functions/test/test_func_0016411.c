void InstanceKlass::release_C_heap_structures() {


  if (_oop_map_cache != NULL) {
    delete _oop_map_cache;
    _oop_map_cache = NULL;
  }


  JNIid::deallocate(jni_ids());
  set_jni_ids(NULL);

  jmethodID* jmeths = methods_jmethod_ids_acquire();
  if (jmeths != (jmethodID*)NULL) {
    release_set_methods_jmethod_ids(NULL);
    FreeHeap(jmeths);
  }


  dependencies().wipe();

#if INCLUDE_JVMTI

  if (breakpoints() != 0x0) {
    methods_do(clear_all_breakpoints);
    assert(breakpoints() == 0x0, "should have cleared breakpoints");
  }


  if (_cached_class_file != NULL && !MetaspaceShared::is_in_shared_metaspace(_cached_class_file)) {
    os::free(_cached_class_file);
    _cached_class_file = NULL;
  }
#endif


  if (_name != NULL) _name->decrement_refcount();


  if (_array_name != NULL)  _array_name->decrement_refcount();
  if (_source_debug_extension != NULL) FREE_C_HEAP_ARRAY(char, _source_debug_extension);
}
