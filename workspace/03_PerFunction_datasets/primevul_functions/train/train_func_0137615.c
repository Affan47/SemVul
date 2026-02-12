void InstanceKlass::restore_unshareable_info(ClassLoaderData* loader_data, Handle protection_domain,
                                             PackageEntry* pkg_entry, TRAPS) {


  assert(!is_loaded(), "invalid init state");
  assert(!shared_loading_failed(), "Must not try to load failed class again");
  set_package(loader_data, pkg_entry, CHECK);
  Klass::restore_unshareable_info(loader_data, protection_domain, CHECK);

  Array<Method*>* methods = this->methods();
  int num_methods = methods->length();
  for (int index = 0; index < num_methods; ++index) {
    methods->at(index)->restore_unshareable_info(CHECK);
  }
#if INCLUDE_JVMTI
  if (JvmtiExport::has_redefined_a_class()) {


    bool trace_name_printed = false;
    adjust_default_methods(&trace_name_printed);
    vtable().initialize_vtable();
    itable().initialize_itable();
  }
#endif


  constants()->restore_unshareable_info(CHECK);

  if (array_klasses() != NULL) {


    array_klasses()->restore_unshareable_info(ClassLoaderData::the_null_class_loader_data(), Handle(), CHECK);
  }


  if (UseBiasedLocking && BiasedLocking::enabled()) {
    set_prototype_header(markWord::biased_locking_prototype());
  }


  if (DiagnoseSyncOnValueBasedClasses && has_value_based_class_annotation()) {
    set_is_value_based();
    set_prototype_header(markWord::prototype());
  }
}
