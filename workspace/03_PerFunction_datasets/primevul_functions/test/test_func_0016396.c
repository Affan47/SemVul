jmethodID InstanceKlass::get_jmethod_id(const methodHandle& method_h) {
  size_t idnum = (size_t)method_h->method_idnum();
  jmethodID* jmeths = methods_jmethod_ids_acquire();
  size_t length = 0;
  jmethodID id = NULL;


  if (jmeths != NULL) {

    if (!idnum_can_increment()) {

      get_jmethod_id_length_value(jmeths, idnum, &length, &id);
    } else {

      if (Threads::number_of_threads() == 0 ||
          SafepointSynchronize::is_at_safepoint()) {

        get_jmethod_id_length_value(jmeths, idnum, &length, &id);
      } else {
        MutexLockerEx ml(JmethodIdCreation_lock, Mutex::_no_safepoint_check_flag);
        get_jmethod_id_length_value(jmeths, idnum, &length, &id);
      }
    }
  }


  if (jmeths == NULL ||
      length <= idnum ||
      id == NULL) {


    jmethodID  to_dealloc_id     = NULL;
    jmethodID* to_dealloc_jmeths = NULL;


    jmethodID* new_jmeths = NULL;
    if (length <= idnum) {

      size_t size = MAX2(idnum+1, (size_t)idnum_allocated_count());
      new_jmeths = NEW_C_HEAP_ARRAY(jmethodID, size+1, mtClass);
      memset(new_jmeths, 0, (size+1)*sizeof(jmethodID));

      new_jmeths[0] = (jmethodID)size;
    }


    jmethodID new_id = NULL;
    if (method_h->is_old() && !method_h->is_obsolete()) {

      Method* current_method = method_with_idnum((int)idnum);
      assert(current_method != NULL, "old and but not obsolete, so should exist");
      new_id = Method::make_jmethod_id(class_loader_data(), current_method);
    } else {


      new_id = Method::make_jmethod_id(class_loader_data(), method_h());
    }

    if (Threads::number_of_threads() == 0 ||
        SafepointSynchronize::is_at_safepoint()) {

      id = get_jmethod_id_fetch_or_update(idnum, new_id, new_jmeths,
                                          &to_dealloc_id, &to_dealloc_jmeths);
    } else {
      MutexLockerEx ml(JmethodIdCreation_lock, Mutex::_no_safepoint_check_flag);
      id = get_jmethod_id_fetch_or_update(idnum, new_id, new_jmeths,
                                          &to_dealloc_id, &to_dealloc_jmeths);
    }


    if (to_dealloc_jmeths != NULL) {
      FreeHeap(to_dealloc_jmeths);
    }

    if (to_dealloc_id != NULL) {
      Method::destroy_jmethod_id(class_loader_data(), to_dealloc_id);
    }
  }
  return id;
}
