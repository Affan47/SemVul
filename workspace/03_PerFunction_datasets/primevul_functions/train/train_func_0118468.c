void ciEnv::register_method(ciMethod* target,
                            int entry_bci,
                            CodeOffsets* offsets,
                            int orig_pc_offset,
                            CodeBuffer* code_buffer,
                            int frame_words,
                            OopMapSet* oop_map_set,
                            ExceptionHandlerTable* handler_table,
                            ImplicitExceptionTable* inc_table,
                            AbstractCompiler* compiler,
                            bool has_unsafe_access,
                            bool has_wide_vectors,
                            RTMState  rtm_state) {
  VM_ENTRY_MARK;
  nmethod* nm = NULL;
  {
    methodHandle method(THREAD, target->get_Method());


    if (method->get_method_counters(THREAD) == NULL) {
      record_failure("can't create method counters");


      code_buffer->free_blob();
      return;
    }


    MutexLocker locker(MethodCompileQueue_lock, THREAD);


    MutexLocker ml(Compile_lock);
    NoSafepointVerifier nsv;


    if (!failing() && jvmti_state_changed()) {
      record_failure("Jvmti state change invalidated dependencies");
    }


    if (!failing() &&
        ( (!dtrace_extended_probes() && ExtendedDTraceProbes) ||
          (!dtrace_method_probes() && DTraceMethodProbes) ||
          (!dtrace_alloc_probes() && DTraceAllocProbes) )) {
      record_failure("DTrace flags change invalidated dependencies");
    }

    if (!failing()) {
      if (log() != NULL) {

        dependencies()->log_all_dependencies();
      }


      dependencies()->encode_content_bytes();


      validate_compile_task_dependencies(target);
    }
#if INCLUDE_RTM_OPT
    if (!failing() && (rtm_state != NoRTM) &&
        (method()->method_data() != NULL) &&
        (method()->method_data()->rtm_state() != rtm_state)) {

      record_failure("RTM state change invalidated rtm code");
    }
#endif

    if (failing()) {

      MethodData* mdo = method()->method_data();
      if (mdo != NULL && _inc_decompile_count_on_failure) {
        mdo->inc_decompile_count();
      }


      code_buffer->free_blob();
      return;
    }

    assert(offsets->value(CodeOffsets::Deopt) != -1, "must have deopt entry");
    assert(offsets->value(CodeOffsets::Exceptions) != -1, "must have exception entry");

    nm =  nmethod::new_nmethod(method,
                               compile_id(),
                               entry_bci,
                               offsets,
                               orig_pc_offset,
                               debug_info(), dependencies(), code_buffer,
                               frame_words, oop_map_set,
                               handler_table, inc_table,
                               compiler, task()->comp_level());


    code_buffer->free_blob();

    if (nm != NULL) {
      nm->set_has_unsafe_access(has_unsafe_access);
      nm->set_has_wide_vectors(has_wide_vectors);
#if INCLUDE_RTM_OPT
      nm->set_rtm_state(rtm_state);
#endif


      if (task() != NULL) {
        task()->set_code(nm);
      }

      if (entry_bci == InvocationEntryBci) {
        if (TieredCompilation) {

          CompiledMethod* old = method->code();
          if (TraceMethodReplacement && old != NULL) {
            ResourceMark rm;
            char *method_name = method->name_and_sig_as_C_string();
            tty->print_cr("Replacing method %s", method_name);
          }
          if (old != NULL) {
            old->make_not_used();
          }
        }
        if (TraceNMethodInstalls) {
          ResourceMark rm;
          char *method_name = method->name_and_sig_as_C_string();
          ttyLocker ttyl;
          tty->print_cr("Installing method (%d) %s ",
                        task()->comp_level(),
                        method_name);
        }

        method->set_code(method, nm);
      } else {
        if (TraceNMethodInstalls) {
          ResourceMark rm;
          char *method_name = method->name_and_sig_as_C_string();
          ttyLocker ttyl;
          tty->print_cr("Installing osr method (%d) %s @ %d",
                        task()->comp_level(),
                        method_name,
                        entry_bci);
        }
        method->method_holder()->add_osr_nmethod(nm);
      }
      nm->make_in_use();
    }
  }

  if (nm != NULL) {

    nm->post_compiled_method_load_event();
  } else {

    record_failure("code cache is full");
  }
}
