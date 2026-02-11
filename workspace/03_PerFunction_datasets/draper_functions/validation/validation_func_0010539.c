long_prune_init()
{
  const unsigned int N = get_nof_vertices();
  long_prune_temp.clear();
  long_prune_temp.resize(N);


  const unsigned int nof_fitting_in_max_mem =
    (long_prune_options_max_mem * 1024 * 1024) / (((N * 2) / 8)+1);
  long_prune_max_stored_autss = long_prune_options_max_stored_auts;


  if(nof_fitting_in_max_mem < long_prune_options_max_stored_auts)
    long_prune_max_stored_autss = nof_fitting_in_max_mem;

  long_prune_deallocate();
  long_prune_fixed.resize(N, 0);
  long_prune_mcrs.resize(N, 0);
  long_prune_begin = 0;
  long_prune_end = 0;
}
