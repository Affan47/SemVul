jmethodID InstanceKlass::jmethod_id_or_null(Method* method) {
  size_t idnum = (size_t)method->method_idnum();
  jmethodID* jmeths = methods_jmethod_ids_acquire();
  size_t length;
  jmethodID id = NULL;
  if (jmeths != NULL &&
      (length = (size_t)jmeths[0]) > idnum) {
    id = jmeths[idnum+1];
  }
  return id;
}
