void LinkResolver::resolve_dynamic_call(CallInfo& result,
                                        BootstrapInfo& bootstrap_specifier,
                                        TRAPS) {


  SystemDictionary::invoke_bootstrap_method(bootstrap_specifier, THREAD);
  Exceptions::wrap_dynamic_exception( true, THREAD);

  if (HAS_PENDING_EXCEPTION) {
    if (!PENDING_EXCEPTION->is_a(vmClasses::LinkageError_klass())) {


      return;
    }


     bool recorded_res_status = bootstrap_specifier.save_and_throw_indy_exc(CHECK);
     if (!recorded_res_status) {


       bool is_done = bootstrap_specifier.resolve_previously_linked_invokedynamic(result, CHECK);
       if (is_done) return;
     }
     assert(bootstrap_specifier.invokedynamic_cp_cache_entry()->indy_resolution_failed(),
            "Resolution failure flag wasn't set");
  }

  bootstrap_specifier.resolve_newly_linked_invokedynamic(result, CHECK);


}
