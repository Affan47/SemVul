commit_max(bw_array_t *b)
{

  b->totals[b->next_max_idx] = b->total_in_period;

  b->maxima[b->next_max_idx++] = b->max_total;

  b->next_period += NUM_SECS_BW_SUM_INTERVAL;
  if (b->next_max_idx == NUM_TOTALS)
    b->next_max_idx = 0;
  if (b->num_maxes_set < NUM_TOTALS)
    ++b->num_maxes_set;

  b->max_total = 0;

  b->total_in_period = 0;
}
