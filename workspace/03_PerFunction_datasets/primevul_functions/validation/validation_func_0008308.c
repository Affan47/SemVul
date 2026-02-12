void blosc_set_delta(int dodelta) {

  g_delta = dodelta;


  if (!g_initlib) blosc_init();

}
