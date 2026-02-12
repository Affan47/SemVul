int blosc_set_nthreads(int nthreads_new) {
  int ret = g_nthreads;


  if (!g_initlib) blosc_init();

 if (nthreads_new != ret) {
   g_nthreads = nthreads_new;
   g_global_context->new_nthreads = nthreads_new;
   check_nthreads(g_global_context);
 }

  return ret;
}
