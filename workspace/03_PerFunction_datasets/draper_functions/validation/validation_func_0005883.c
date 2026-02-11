verify_quality(const stp_vars_t *v, const quality_t *q)
{
  unsigned max_x, max_y, min_x, min_y;
  get_printer_resolution_bounds(v, &max_x, &max_y, &min_x, &min_y);
  if ((q->max_vres == 0 || min_y <= q->max_vres) &&
      (q->min_vres == 0 || max_y >= q->min_vres) &&
      (q->max_hres == 0 || min_x <= q->max_hres) &&
      (q->min_hres == 0 || max_x >= q->min_hres))
    {
      stp_dprintf(STP_DBG_ESCP2, v, "Quality %s OK: %d %d %d %d\n",
		  q->text, q->min_hres, q->min_vres, q->max_hres, q->max_vres);
      return 1;
    }
  else
    {
      stp_dprintf(STP_DBG_ESCP2, v, "Quality %s not OK: %d %d %d %d\n",
		  q->text, q->min_hres, q->min_vres, q->max_hres, q->max_vres);
      return 0;
    }
}
