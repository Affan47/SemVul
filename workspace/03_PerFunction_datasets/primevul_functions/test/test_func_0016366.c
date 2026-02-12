bool InstanceKlass::remove_osr_nmethod(nmethod* n) {

  MutexLockerEx ml(OsrList_lock, Mutex::_no_safepoint_check_flag);
  assert(n->is_osr_method(), "wrong kind of nmethod");
  nmethod* last = NULL;
  nmethod* cur  = osr_nmethods_head();
  int max_level = CompLevel_none;
  Method* m = n->method();

  bool found = false;
  while(cur != NULL && cur != n) {
    if (TieredCompilation && m == cur->method()) {

      max_level = MAX2(max_level, cur->comp_level());
    }
    last = cur;
    cur = cur->osr_link();
  }
  nmethod* next = NULL;
  if (cur == n) {
    found = true;
    next = cur->osr_link();
    if (last == NULL) {

      set_osr_nmethods_head(next);
    } else {
      last->set_osr_link(next);
    }
  }
  n->set_osr_link(NULL);
  if (TieredCompilation) {
    cur = next;
    while (cur != NULL) {

      if (m == cur->method()) {
        max_level = MAX2(max_level, cur->comp_level());
      }
      cur = cur->osr_link();
    }
    m->set_highest_osr_comp_level(max_level);
  }
  return found;
}
