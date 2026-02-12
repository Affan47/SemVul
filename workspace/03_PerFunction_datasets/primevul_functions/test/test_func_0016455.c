void InstanceKlass::remove_unshareable_info() {
  Klass::remove_unshareable_info();

  if (is_in_error_state()) {


    return;
  }


  _init_state = allocated;

  {
    MutexLocker ml(Compile_lock);
    init_implementor();
  }

  constants()->remove_unshareable_info();

  for (int i = 0; i < methods()->length(); i++) {
    Method* m = methods()->at(i);
    m->remove_unshareable_info();
  }


  if (array_klasses() != NULL) {
    array_klasses()->remove_unshareable_info();
  }


  guarantee(_source_debug_extension == NULL, "must be");
  guarantee(_dep_context == DependencyContext::EMPTY, "must be");
  guarantee(_osr_nmethods_head == NULL, "must be");

#if INCLUDE_JVMTI
  guarantee(_breakpoints == NULL, "must be");
  guarantee(_previous_versions == NULL, "must be");
#endif

  _init_thread = NULL;
  _methods_jmethod_ids = NULL;
  _jni_ids = NULL;
  _oop_map_cache = NULL;

  _nest_host = NULL;
}
