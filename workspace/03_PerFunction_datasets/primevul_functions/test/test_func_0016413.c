void InstanceKlass::deallocate_contents(ClassLoaderData* loader_data) {


  if (java_mirror() != NULL) {
    java_lang_Class::set_klass(java_mirror(), NULL);
  }


  loader_data->remove_handle(_java_mirror);


  loader_data->remove_class(this);


  assert(array_klasses() == NULL, "array classes shouldn't be created for this class yet");


  release_C_heap_structures();

  deallocate_methods(loader_data, methods());
  set_methods(NULL);

  if (method_ordering() != NULL &&
      method_ordering() != Universe::the_empty_int_array() &&
      !method_ordering()->is_shared()) {
    MetadataFactory::free_array<int>(loader_data, method_ordering());
  }
  set_method_ordering(NULL);


  if (default_methods() != NULL &&
      default_methods() != Universe::the_empty_method_array() &&
      !default_methods()->is_shared()) {
    MetadataFactory::free_array<Method*>(loader_data, default_methods());
  }

  set_default_methods(NULL);


  if (default_vtable_indices() != NULL &&
      !default_vtable_indices()->is_shared()) {
    MetadataFactory::free_array<int>(loader_data, default_vtable_indices());
  }
  set_default_vtable_indices(NULL);


  if (secondary_supers() != NULL &&
      secondary_supers() != Universe::the_empty_klass_array() &&
      secondary_supers() != transitive_interfaces() &&
      !secondary_supers()->is_shared()) {
    MetadataFactory::free_array<Klass*>(loader_data, secondary_supers());
  }
  set_secondary_supers(NULL);

  deallocate_interfaces(loader_data, super(), local_interfaces(), transitive_interfaces());
  set_transitive_interfaces(NULL);
  set_local_interfaces(NULL);

  if (fields() != NULL && !fields()->is_shared()) {
    MetadataFactory::free_array<jushort>(loader_data, fields());
  }
  set_fields(NULL, 0);


  if (constants() != NULL) {
    assert (!constants()->on_stack(), "shouldn't be called if anything is onstack");
    if (!constants()->is_shared()) {
      MetadataFactory::free_metadata(loader_data, constants());
    }

    SystemDictionary::delete_resolution_error(constants());

    set_constants(NULL);
  }

  if (inner_classes() != NULL &&
      inner_classes() != Universe::the_empty_short_array() &&
      !inner_classes()->is_shared()) {
    MetadataFactory::free_array<jushort>(loader_data, inner_classes());
  }
  set_inner_classes(NULL);

  if (nest_members() != NULL &&
      nest_members() != Universe::the_empty_short_array() &&
      !nest_members()->is_shared()) {
    MetadataFactory::free_array<jushort>(loader_data, nest_members());
  }
  set_nest_members(NULL);


  if (annotations() != NULL && !annotations()->is_shared()) {
    MetadataFactory::free_metadata(loader_data, annotations());
  }
  set_annotations(NULL);
}
