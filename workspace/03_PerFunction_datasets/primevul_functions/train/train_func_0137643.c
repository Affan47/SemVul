void InstanceKlass::remove_unshareable_info() {

  if (can_be_verified_at_dumptime()) {

    set_verified_at_dump_time();
  }

  Klass::remove_unshareable_info();

  if (SystemDictionaryShared::has_class_failed_verification(this)) {


    return;
  }


  _init_state = allocated;

  {
    assert(SafepointSynchronize::is_at_safepoint(), "only called at safepoint");
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


  _source_debug_extension = NULL;
  _dep_context = NULL;
  _osr_nmethods_head = NULL;
#if INCLUDE_JVMTI
  _breakpoints = NULL;
  _previous_versions = NULL;
  _cached_class_file = NULL;
  _jvmti_cached_class_field_map = NULL;
#endif

  _init_thread = NULL;
  _methods_jmethod_ids = NULL;
  _jni_ids = NULL;
  _oop_map_cache = NULL;

  _nest_host = NULL;
  init_shared_package_entry();
  _dep_context_last_cleaned = 0;
}
