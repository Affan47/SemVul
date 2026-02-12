aubio_filterbank_do (aubio_filterbank_t * f, const cvec_t * in, fvec_t * out)
{


  fvec_t tmp;
  tmp.length = in->length;
  tmp.data = in->norm;

  if (f->power != 1.) fvec_pow(&tmp, f->power);

  fmat_vecmul(f->filters, &tmp, out);

  return;
}
