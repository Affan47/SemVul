void InstanceKlass::get_jmethod_id_length_value(jmethodID* cache,
       size_t idnum, size_t *length_p, jmethodID* id_p) {
  assert(cache != NULL, "sanity check");
  assert(length_p != NULL, "sanity check");
  assert(id_p != NULL, "sanity check");


  *length_p = (size_t)cache[0];
  if (*length_p <= idnum) {
    *id_p = NULL;
  } else {
    *id_p = cache[idnum+1];
  }
}
