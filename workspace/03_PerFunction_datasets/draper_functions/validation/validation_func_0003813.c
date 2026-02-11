soxr_output_no_callback(soxr_t p, soxr_buf_t out, size_t len)
{
  unsigned u;
  size_t done = 0;
  bool separated = !!(p->io_spec.otype & SOXR_SPLIT);
#if defined _OPENMP
  int i;
  if (!p->runtime_spec.num_threads && p->num_channels > 1)
#pragma omp parallel for
  for (i = 0; i < (int)p->num_channels; ++i) {
    size_t done1;
    done1 = soxr_output_1ch(p, (unsigned)i, ((soxr_bufs_t)out)[i], len, separated);
    if (!i)
      done = done1;
  } else
#endif
  for (u = 0; u < p->num_channels; ++u)
    done = soxr_output_1ch(p, u, ((soxr_bufs_t)out)[u], len, separated);

  if (!separated)
    p->clips += (p->interleave)(p->io_spec.otype, &out, (sample_t const * const *)p->channel_ptrs,
        done, p->num_channels, (p->io_spec.flags & SOXR_NO_DITHER)? 0 : &p->seed);
  return done;
}
