pwg_free_finishings(
    _pwg_finishings_t *f)
{
  cupsFreeOptions(f->num_options, f->options);
  free(f);
}
