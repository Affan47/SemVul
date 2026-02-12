void InstanceKlass::verify_on(outputStream* st) {
#ifndef PRODUCT

  if (_verify_count == Universe::verify_count()) return;
  _verify_count = Universe::verify_count();
#endif


  Klass::verify_on(st);


  guarantee(class_loader_data()->contains_klass(this),
            "this class isn't found in class loader data");


  if (is_linked()) {


    vtable().verify(st);
  }


  if (subklass() != NULL) {
    guarantee(subklass()->is_klass(), "should be klass");
  }


  Klass* super = this->super();
  Klass* sib = next_sibling();
  if (sib != NULL) {
    if (sib == this) {
      fatal("subclass points to itself " PTR_FORMAT, p2i(sib));
    }

    guarantee(sib->is_klass(), "should be klass");
    guarantee(sib->super() == super, "siblings should have same superklass");
  }


  if (local_interfaces()) {
    Array<Klass*>* local_interfaces = this->local_interfaces();
    for (int j = 0; j < local_interfaces->length(); j++) {
      Klass* e = local_interfaces->at(j);
      guarantee(e->is_klass() && e->is_interface(), "invalid local interface");
    }
  }


  if (transitive_interfaces() != NULL) {
    Array<Klass*>* transitive_interfaces = this->transitive_interfaces();
    for (int j = 0; j < transitive_interfaces->length(); j++) {
      Klass* e = transitive_interfaces->at(j);
      guarantee(e->is_klass() && e->is_interface(), "invalid transitive interface");
    }
  }


  if (methods() != NULL) {
    Array<Method*>* methods = this->methods();
    for (int j = 0; j < methods->length(); j++) {
      guarantee(methods->at(j)->is_method(), "non-method in methods array");
    }
    for (int j = 0; j < methods->length() - 1; j++) {
      Method* m1 = methods->at(j);
      Method* m2 = methods->at(j + 1);
      guarantee(m1->name()->fast_compare(m2->name()) <= 0, "methods not sorted correctly");
    }
  }


  if (method_ordering() != NULL) {
    Array<int>* method_ordering = this->method_ordering();
    int length = method_ordering->length();
    if (JvmtiExport::can_maintain_original_method_order() ||
        ((UseSharedSpaces || DumpSharedSpaces) && length != 0)) {
      guarantee(length == methods()->length(), "invalid method ordering length");
      jlong sum = 0;
      for (int j = 0; j < length; j++) {
        int original_index = method_ordering->at(j);
        guarantee(original_index >= 0, "invalid method ordering index");
        guarantee(original_index < length, "invalid method ordering index");
        sum += original_index;
      }

      guarantee(sum == ((jlong)length*(length-1))/2, "invalid method ordering sum");
    } else {
      guarantee(length == 0, "invalid method ordering length");
    }
  }


  if (default_methods() != NULL) {
    Array<Method*>* methods = this->default_methods();
    for (int j = 0; j < methods->length(); j++) {
      guarantee(methods->at(j)->is_method(), "non-method in methods array");
    }
    for (int j = 0; j < methods->length() - 1; j++) {
      Method* m1 = methods->at(j);
      Method* m2 = methods->at(j + 1);
      guarantee(m1->name()->fast_compare(m2->name()) <= 0, "methods not sorted correctly");
    }
  }


  if (jni_ids() != NULL) {
    jni_ids()->verify(this);
  }


  if (array_klasses() != NULL) {
    guarantee(array_klasses()->is_klass(), "should be klass");
  }
  if (constants() != NULL) {
    guarantee(constants()->is_constantPool(), "should be constant pool");
  }
  const Klass* host = host_klass();
  if (host != NULL) {
    guarantee(host->is_klass(), "should be klass");
  }
}
