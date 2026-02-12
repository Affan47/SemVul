jmethodID InstanceKlass::get_jmethod_id_fetch_or_update(
            size_t idnum, jmethodID new_id,
            jmethodID* new_jmeths, jmethodID* to_dealloc_id_p,
            jmethodID** to_dealloc_jmeths_p) {
  assert(new_id != NULL, "sanity check");
  assert(to_dealloc_id_p != NULL, "sanity check");
  assert(to_dealloc_jmeths_p != NULL, "sanity check");
  assert(Threads::number_of_threads() == 0 ||
         SafepointSynchronize::is_at_safepoint() ||
         JmethodIdCreation_lock->owned_by_self(), "sanity check");


  jmethodID* jmeths = methods_jmethod_ids_acquire();
  jmethodID  id     = NULL;
  size_t     length = 0;

  if (jmeths == NULL ||
      (length = (size_t)jmeths[0]) <= idnum) {
    if (jmeths != NULL) {

      for (size_t index = 0; index < length; index++) {
        new_jmeths[index+1] = jmeths[index+1];
      }
      *to_dealloc_jmeths_p = jmeths;
    }
    release_set_methods_jmethod_ids(jmeths = new_jmeths);
  } else {

    id = jmeths[idnum+1];
    *to_dealloc_jmeths_p = new_jmeths;
  }
  if (id == NULL) {


    id = new_id;


    Atomic::release_store(&jmeths[idnum+1], id);
  } else {
    *to_dealloc_id_p = new_id;
  }
  return id;
}
