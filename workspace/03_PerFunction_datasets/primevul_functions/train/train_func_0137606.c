void InstanceKlass::set_package(ClassLoaderData* loader_data, PackageEntry* pkg_entry, TRAPS) {


  if (!is_shared()) {
    check_prohibited_package(name(), loader_data, CHECK);
  }

  if (is_shared() && _package_entry != NULL) {
    if (MetaspaceShared::use_full_module_graph() && _package_entry == pkg_entry) {

      assert(MetaspaceShared::is_in_shared_metaspace(_package_entry), "must be");
      return;
    } else {
      _package_entry = NULL;
    }
  }


  TempNewSymbol from_class_name =
      (pkg_entry != NULL) ? NULL : ClassLoader::package_from_class_name(name());

  Symbol* pkg_name;
  if (pkg_entry != NULL) {
    pkg_name = pkg_entry->name();
  } else {
    pkg_name = from_class_name;
  }

  if (pkg_name != NULL && loader_data != NULL) {


    _package_entry = pkg_entry != NULL ? pkg_entry : loader_data->packages()->lookup_only(pkg_name);


    if (_package_entry == NULL) {

      if (!ModuleEntryTable::javabase_defined()) {


        assert(ModuleEntryTable::javabase_moduleEntry() != NULL, JAVA_BASE_NAME " module is NULL");
        _package_entry = loader_data->packages()->lookup(pkg_name, ModuleEntryTable::javabase_moduleEntry());
      } else {
        assert(loader_data->unnamed_module() != NULL, "unnamed module is NULL");
        _package_entry = loader_data->packages()->lookup(pkg_name,
                                                         loader_data->unnamed_module());
      }


      DEBUG_ONLY(ResourceMark rm(THREAD));
      assert(_package_entry != NULL, "Package entry for class %s not found, loader %s",
             name()->as_C_string(), loader_data->loader_name_and_id());
    }

    if (log_is_enabled(Debug, module)) {
      ResourceMark rm(THREAD);
      ModuleEntry* m = _package_entry->module();
      log_trace(module)("Setting package: class: %s, package: %s, loader: %s, module: %s",
                        external_name(),
                        pkg_name->as_C_string(),
                        loader_data->loader_name_and_id(),
                        (m->is_named() ? m->name()->as_C_string() : UNNAMED_MODULE));
    }
  } else {
    ResourceMark rm(THREAD);
    log_trace(module)("Setting package: class: %s, package: unnamed, loader: %s, module: %s",
                      external_name(),
                      (loader_data != NULL) ? loader_data->loader_name_and_id() : "NULL",
                      UNNAMED_MODULE);
  }
}
