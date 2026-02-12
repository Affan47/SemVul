void ciEnv::validate_compile_task_dependencies(ciMethod* target) {
  if (failing())  return;


  for (Dependencies::DepStream deps(dependencies()); deps.next(); ) {
    if (deps.is_klass_type())  continue;
    Klass* witness = deps.check_dependency();
    if (witness != NULL) {
      record_failure("invalid non-klass dependency");
      return;
    }
  }


  bool counter_changed = system_dictionary_modification_counter_changed();

  bool verify_deps = trueInDebug;
  if (!counter_changed && !verify_deps)  return;

  int klass_violations = 0;
  for (Dependencies::DepStream deps(dependencies()); deps.next(); ) {
    if (!deps.is_klass_type())  continue;
    Klass* witness = deps.check_dependency();
    if (witness != NULL) {
      klass_violations++;
      if (!counter_changed) {


        deps.print_dependency(witness);
      } else if (xtty == NULL) {


        break;
      }
    }
  }

  if (klass_violations != 0) {
#ifdef ASSERT
    if (!counter_changed && !PrintCompilation) {

      _task->print_line();
    }
#endif
    assert(counter_changed, "failed dependencies, but counter didn't change");
    record_failure("concurrent class loading");
  }
}
