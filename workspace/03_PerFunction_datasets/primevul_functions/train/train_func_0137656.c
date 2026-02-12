InstanceKlass* InstanceKlass::allocate_instance_klass(const ClassFileParser& parser, TRAPS) {
  const int size = InstanceKlass::size(parser.vtable_size(),
                                       parser.itable_size(),
                                       nonstatic_oop_map_size(parser.total_oop_map_count()),
                                       parser.is_interface());

  const Symbol* const class_name = parser.class_name();
  assert(class_name != NULL, "invariant");
  ClassLoaderData* loader_data = parser.loader_data();
  assert(loader_data != NULL, "invariant");

  InstanceKlass* ik;


  if (REF_NONE == parser.reference_type()) {
    if (class_name == vmSymbols::java_lang_Class()) {

      ik = new (loader_data, size, THREAD) InstanceMirrorKlass(parser);
    }
    else if (is_class_loader(class_name, parser)) {

      ik = new (loader_data, size, THREAD) InstanceClassLoaderKlass(parser);
    } else {

      ik = new (loader_data, size, THREAD) InstanceKlass(parser, InstanceKlass::_kind_other);
    }
  } else {

    ik = new (loader_data, size, THREAD) InstanceRefKlass(parser);
  }


  if (HAS_PENDING_EXCEPTION) {
    return NULL;
  }

  return ik;
}
