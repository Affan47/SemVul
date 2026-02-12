void optimized_ops_preload_l1_stream(const T* ptr) {
#ifdef __GNUC__

  __builtin_prefetch(ptr,  0,  0);
#else
  (void)ptr;
#endif
}
