test_main_thread() {
  int i, m;
  char b[128];
  MutexLock ml(&mutex);
  for (m = 0; m < 1000000; ++m) {
    for (i = 0; i < g_iters; ++i ) {
      result ^= i;
    }
    snprintf(b, sizeof(b), "same: %d", result);
  }
}
