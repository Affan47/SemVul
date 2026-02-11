best_overlap_offset_s16 (GstScaletempo * scaletempo)
{
  GstScaletempoPrivate *p = GST_SCALETEMPO_GET_PRIVATE (scaletempo);
  gint32 *pw, *ppc;
  gint16 *po, *search_start;
  gint64 best_corr = G_MININT64;
  guint best_off = 0;
  guint off;
  glong i;

  pw = p->table_window;
  po = p->buf_overlap;
  po += p->samples_per_frame;
  ppc = p->buf_pre_corr;
  for (i = p->samples_per_frame; i < p->samples_overlap; i++) {
    *ppc++ = (*pw++ * *po++) >> 15;
  }

  search_start = (gint16 *) p->buf_queue + p->samples_per_frame;
  for (off = 0; off < p->frames_search; off++) {
    gint64 corr = 0;
    gint16 *ps = search_start;
    ppc = p->buf_pre_corr;
    ppc += p->samples_overlap - p->samples_per_frame;
    ps += p->samples_overlap - p->samples_per_frame;
    i = -((glong) p->samples_overlap - (glong) p->samples_per_frame);
    do {
      corr += ppc[i + 0] * ps[i + 0];
      corr += ppc[i + 1] * ps[i + 1];
      corr += ppc[i + 2] * ps[i + 2];
      corr += ppc[i + 3] * ps[i + 3];
      i += 4;
    } while (i < 0);
    if (corr > best_corr) {
      best_corr = corr;
      best_off = off;
    }
    search_start += p->samples_per_frame;
  }

  return best_off * p->bytes_per_frame;
}
