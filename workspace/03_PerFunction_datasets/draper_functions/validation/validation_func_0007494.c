RecordLazyDeoptimizationIndex(int index) {
  while (last_lazy_safepoint_ < deopt_index_list_.length()) {
    deopt_index_list_[last_lazy_safepoint_++] = index;
  }
}
