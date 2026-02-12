void InstanceKlass::set_package(ClassLoaderData* loader_data, TRAPS) {


  check_prohibited_package(name(), loader_data, CHECK);

  TempNewSymbol pkg_name = package_from_name(name(), CHECK);

  if (pkg_name != NULL && loader_data != NULL) {


    _package_entry = loader_data->packages()->lookup_only(pkg_name);


    if (_package_entry == NULL) {
      ResourceMark rm;

      if (!ModuleEntryTable::javabase_defined()) {


        assert(ModuleEntryTable::javabase_moduleEntry() != NULL, JAVA_BASE_NAME " module is NULL");
        _package_entry = loader_data->packages()->lookup(pkg_name, ModuleEntryTable::javabase_moduleEntry());
      } else {
        assert(loader_data->unnamed_module() != NULL, "unnamed module is NULL");
        _package_entry = loader_data->packages()->lookup(pkg_name,
                                                         loader_data->unnamed_module());
      }


      assert(_package_entry != NULL, "Package entry for class %s not found, loader %s",
             name()->as_C_string(), loader_data->loader_name_and_id());
    }

    if (log_is_enabled(Debug, module)) {
      ResourceMark rm;
      ModuleEntry* m = _package_entry->module();
      log_trace(module)("Setting package: class: %s, package: %s, loader: %s, module: %s",
                        external_name(),
                        pkg_name->as_C_string(),
                        loader_data->loader_name_and_id(),
                        (m->is_named() ? m->name()->as_C_string() : UNNAMED_MODULE));
    }
  } else {
    ResourceMark rm;
    log_trace(module)("Setting package: class: %s, package: unnamed, loader: %s, module: %s",
                      external_name(),
                      (loader_data != NULL) ? loader_data->loader_name_and_id() : "NULL",
                      UNNAMED_MODULE);
  }
}
