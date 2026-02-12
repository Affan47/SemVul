check_unique_ts(struct timeval *ts, struct timeval *now)
{
  TimestampCell *last_valid, *cell, *next;
  int ok;

  ok = 1;
  last_valid = &(seen_ts_list);
  cell = last_valid->next;

  while (cell) {
    next = cell->next;

    if ((now->tv_sec - cell->ts.tv_sec) > TS_MARGIN) {
      release_ts_cell(cell);
      last_valid->next = next;
    } else {

      last_valid->next = cell;
      last_valid = cell;
      if ((cell->ts.tv_sec == ts->tv_sec) && (cell->ts.tv_usec == ts->tv_usec)) {
        ok = 0;
      }
    }
    cell = next;
  }

  if (ok) {

    cell = allocate_ts_cell();
    last_valid->next = cell;
    cell->next = NULL;
    cell->ts = *ts;
  }

  return ok;
}
