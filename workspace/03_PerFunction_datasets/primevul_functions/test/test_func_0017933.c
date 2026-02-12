Method* LinkResolver::lookup_method_in_klasses(const LinkInfo& link_info,
                                               bool checkpolymorphism,
                                               bool in_imethod_resolve) {
  NoSafepointVerifier nsv;

  Klass* klass = link_info.resolved_klass();
  Symbol* name = link_info.name();
  Symbol* signature = link_info.signature();


  Method* result = klass->uncached_lookup_method(name, signature, Klass::OverpassLookupMode::skip);

  if (klass->is_array_klass()) {

    return result;
  }

  InstanceKlass* ik = InstanceKlass::cast(klass);


  if (in_imethod_resolve &&
      result != NULL &&
      ik->is_interface() &&
      (result->is_static() || !result->is_public()) &&
      result->method_holder() == vmClasses::Object_klass()) {
    result = NULL;
  }


  if (result == NULL) {
    result = ik->find_method(name, signature);
  }

  if (result == NULL) {
    Array<Method*>* default_methods = ik->default_methods();
    if (default_methods != NULL) {
      result = InstanceKlass::find_method(default_methods, name, signature);
    }
  }

  if (checkpolymorphism && result != NULL) {
    vmIntrinsics::ID iid = result->intrinsic_id();
    if (MethodHandles::is_signature_polymorphic(iid)) {

      return NULL;
    }
  }
  return result;
}
