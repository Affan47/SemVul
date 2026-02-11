ares_destroy_options(struct ares_options *options)
{
  int i;

  if(options->servers)
    free(options->servers);
  for (i = 0; i < options->ndomains; i++)
    free(options->domains[i]);
  free(options->domains);
  if(options->sortlist)
    free(options->sortlist);
  free(options->lookups);
}
