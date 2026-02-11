findDefinedVNInfoForStackInt(unsigned reg) const {
  for (LiveInterval::const_vni_iterator i = vni_begin(), e = vni_end();
       i != e; ++i) {
    if ((*i)->getReg() == reg)
      return *i;
  }
  return 0;
}
