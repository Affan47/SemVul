bool InstanceKlass::link_class_impl(TRAPS) {
  if (DumpSharedSpaces && SystemDictionaryShared::has_class_failed_verification(this)) {


    ResourceMark rm(THREAD);
    Exceptions::fthrow(THREAD_AND_LOCATION,
                       vmSymbols::java_lang_NoClassDefFoundError(),
                       "Class %s, or one of its supertypes, failed class initialization",
                       external_name());
    return false;
  }

  if (is_linked()) {
    return true;
  }


  JavaThread* jt = THREAD;


  Klass* super_klass = super();
  if (super_klass != NULL) {
    if (super_klass->is_interface()) {
      ResourceMark rm(THREAD);
      Exceptions::fthrow(
        THREAD_AND_LOCATION,
        vmSymbols::java_lang_IncompatibleClassChangeError(),
        "class %s has interface %s as super class",
        external_name(),
        super_klass->external_name()
      );
      return false;
    }

    InstanceKlass* ik_super = InstanceKlass::cast(super_klass);
    ik_super->link_class_impl(CHECK_false);
  }


  Array<InstanceKlass*>* interfaces = local_interfaces();
  int num_interfaces = interfaces->length();
  for (int index = 0; index < num_interfaces; index++) {
    InstanceKlass* interk = interfaces->at(index);
    interk->link_class_impl(CHECK_false);
  }


  if (is_linked()) {
    return true;
  }


  PerfClassTraceTime vmtimer(ClassLoader::perf_class_link_time(),
                             ClassLoader::perf_class_link_selftime(),
                             ClassLoader::perf_classes_linked(),
                             jt->get_thread_stat()->perf_recursion_counts_addr(),
                             jt->get_thread_stat()->perf_timers_addr(),
                             PerfClassTraceTime::CLASS_LINK);


  {
    HandleMark hm(THREAD);
    Handle h_init_lock(THREAD, init_lock());
    ObjectLocker ol(h_init_lock, jt);


    if (!is_linked()) {
      if (!is_rewritten()) {
        {
          bool verify_ok = verify_code(THREAD);
          if (!verify_ok) {
            return false;
          }
        }


        if (is_linked()) {
          return true;
        }


        rewrite_class(CHECK_false);
      } else if (is_shared()) {
        SystemDictionaryShared::check_verification_constraints(this, CHECK_false);
      }


      link_methods(CHECK_false);


      bool need_init_table = true;
      if (is_shared() && SystemDictionaryShared::check_linking_constraints(THREAD, this)) {
        need_init_table = false;
      }
      if (need_init_table) {
        vtable().initialize_vtable_and_check_constraints(CHECK_false);
        itable().initialize_itable_and_check_constraints(CHECK_false);
      }
#ifdef ASSERT
      vtable().verify(tty, true);


#endif
      if (UseVtableBasedCHA) {
        MutexLocker ml(THREAD, Compile_lock);
        set_init_state(linked);


        if (Universe::is_fully_initialized()) {
          CodeCache::flush_dependents_on(this);
        }
      } else {
        set_init_state(linked);
      }
      if (JvmtiExport::should_post_class_prepare()) {
        JvmtiExport::post_class_prepare(THREAD, this);
      }
    }
  }
  return true;
}
