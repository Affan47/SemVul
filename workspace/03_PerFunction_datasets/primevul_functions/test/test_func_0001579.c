void optimized_ops_prefetch_write_l1_keep(const T* ptr) {
#ifdef __GNUC__

  __builtin_prefetch(ptr,  1,  3);
#else
  (void)ptr;
#endif
}
