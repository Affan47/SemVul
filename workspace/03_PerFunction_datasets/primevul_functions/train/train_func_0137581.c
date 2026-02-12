ModuleEntry* InstanceKlass::module() const {
  if (is_hidden() &&
      in_unnamed_package() &&
      class_loader_data()->has_class_mirror_holder()) {


    if (class_loader_data()->is_boot_class_loader_data()) {
      return ClassLoaderData::the_null_class_loader_data()->unnamed_module();
    } else {
      oop module = java_lang_ClassLoader::unnamedModule(class_loader_data()->class_loader());
      assert(java_lang_Module::is_instance(module), "Not an instance of java.lang.Module");
      return java_lang_Module::module_entry(module);
    }
  }


  if (!in_unnamed_package()) {
    return _package_entry->module();
  }


  return class_loader_data()->unnamed_module();
}
