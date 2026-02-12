void InstanceKlass::clean_weak_instanceklass_links() {
  clean_implementors_list();
  clean_method_data();


  DependencyContext dep_context(&_dep_context);
  dep_context.expunge_stale_entries();
}
