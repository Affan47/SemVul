void LinkResolver::check_method_accessability(Klass* ref_klass,
                                              Klass* resolved_klass,
                                              Klass* sel_klass,
                                              const methodHandle& sel_method,
                                              TRAPS) {

  AccessFlags flags = sel_method->access_flags();


  if (sel_method->name() == vmSymbols::clone_name() &&
      sel_klass == SystemDictionary::Object_klass() &&
      resolved_klass->is_array_klass()) {

    assert(flags.is_protected(), "clone not protected?");
    jint new_flags = flags.as_int();
    new_flags = new_flags & (~JVM_ACC_PROTECTED);
    new_flags = new_flags | JVM_ACC_PUBLIC;
    flags.set_flags(new_flags);
  }


  bool can_access = Reflection::verify_member_access(ref_klass,
                                                     resolved_klass,
                                                     sel_klass,
                                                     flags,
                                                     true, false, CHECK);


  if (!can_access) {
    ResourceMark rm(THREAD);
    bool same_module = (sel_klass->module() == ref_klass->module());
    Exceptions::fthrow(
      THREAD_AND_LOCATION,
      vmSymbols::java_lang_IllegalAccessError(),
      "class %s tried to access %s%s%smethod '%s' (%s%s%s)",
      ref_klass->external_name(),
      sel_method->is_abstract()  ? "abstract "  : "",
      sel_method->is_protected() ? "protected " : "",
      sel_method->is_private()   ? "private "   : "",
      sel_method->external_name(),
      (same_module) ? ref_klass->joint_in_module_of_loader(sel_klass) : ref_klass->class_in_module_of_loader(),
      (same_module) ? "" : "; ",
      (same_module) ? "" : sel_klass->class_in_module_of_loader()
    );
    return;
  }
}
