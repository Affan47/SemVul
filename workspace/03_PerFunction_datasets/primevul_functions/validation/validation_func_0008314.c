int blosc_free_resources(void) {

  if (!g_initlib) return -1;

  return release_threadpool(g_global_context);
}
