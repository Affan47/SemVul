void InstanceKlass::restore_unshareable_info(ClassLoaderData* loader_data, Handle protection_domain, TRAPS) {


  assert(!is_loaded(), "invalid init state");
  set_package(loader_data, CHECK);
  Klass::restore_unshareable_info(loader_data, protection_domain, CHECK);

  Array<Method*>* methods = this->methods();
  int num_methods = methods->length();
  for (int index2 = 0; index2 < num_methods; ++index2) {
    methodHandle m(THREAD, methods->at(index2));
    m->restore_unshareable_info(CHECK);
  }
  if (JvmtiExport::has_redefined_a_class()) {


    ResourceMark rm(THREAD);
    vtable().initialize_vtable(false, CHECK);
    itable().initialize_itable(false, CHECK);
  }


  constants()->restore_unshareable_info(CHECK);

  if (array_klasses() != NULL) {


    array_klasses()->restore_unshareable_info(ClassLoaderData::the_null_class_loader_data(), Handle(), CHECK);
  }
}
