void optimized_ops_preload_l1_keep(const T* ptr) {
#ifdef __GNUC__

  __builtin_prefetch(ptr,  0,  3);
#else
  (void)ptr;
#endif
}
