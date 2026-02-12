Method* InstanceKlass::method_at_itable(InstanceKlass* holder, int index, TRAPS) {
  bool implements_interface;
  Method* m = method_at_itable_or_null(holder, index,
                                       implements_interface);
  if (m != NULL) {
    assert(implements_interface, "sanity");
    return m;
  } else if (implements_interface) {

    THROW_NULL(vmSymbols::java_lang_AbstractMethodError());
  } else {


    ResourceMark rm(THREAD);
    stringStream ss;
    bool same_module = (module() == holder->module());
    ss.print("Receiver class %s does not implement "
             "the interface %s defining the method to be called "
             "(%s%s%s)",
             external_name(), holder->external_name(),
             (same_module) ? joint_in_module_of_loader(holder) : class_in_module_of_loader(),
             (same_module) ? "" : "; ",
             (same_module) ? "" : holder->class_in_module_of_loader());
    THROW_MSG_NULL(vmSymbols::java_lang_IncompatibleClassChangeError(), ss.as_string());
  }
}
