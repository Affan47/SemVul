new_aubio_filterbank (uint_t n_filters, uint_t win_s)
{

  aubio_filterbank_t *fb = AUBIO_NEW (aubio_filterbank_t);

  if ((sint_t)n_filters <= 0) {
    AUBIO_ERR("filterbank: n_filters should be > 0, got %d\n", n_filters);
    goto fail;
  }
  if ((sint_t)win_s <= 0) {
    AUBIO_ERR("filterbank: win_s should be > 0, got %d\n", win_s);
    goto fail;
  }
  fb->win_s = win_s;
  fb->n_filters = n_filters;


  fb->filters = new_fmat (n_filters, win_s / 2 + 1);

  fb->norm = 1;

  fb->power = 1;

  return fb;
fail:
  AUBIO_FREE (fb);
  return NULL;
}
