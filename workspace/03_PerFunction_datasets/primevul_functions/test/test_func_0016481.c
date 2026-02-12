nmethod* InstanceKlass::lookup_osr_nmethod(const Method* m, int bci, int comp_level, bool match_level) const {

  MutexLockerEx ml(OsrList_lock, Mutex::_no_safepoint_check_flag);
  nmethod* osr = osr_nmethods_head();
  nmethod* best = NULL;
  while (osr != NULL) {
    assert(osr->is_osr_method(), "wrong kind of nmethod found in chain");


    if (osr->method() == m &&
        (bci == InvocationEntryBci || osr->osr_entry_bci() == bci)) {
      if (match_level) {
        if (osr->comp_level() == comp_level) {

          return osr;
        }
      } else {
        if (best == NULL || (osr->comp_level() > best->comp_level())) {
          if (osr->comp_level() == CompLevel_highest_tier) {

            return osr;
          }
          best = osr;
        }
      }
    }
    osr = osr->osr_link();
  }

  assert(match_level == false || best == NULL, "shouldn't pick up anything if match_level is set");
  if (best != NULL && best->comp_level() >= comp_level) {
    return best;
  }
  return NULL;
}
