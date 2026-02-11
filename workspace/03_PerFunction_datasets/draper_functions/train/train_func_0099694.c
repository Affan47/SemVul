rep_hist_get_uptime(const char *id, time_t when)
{
  or_history_t *hist = get_or_history(id);
  if (!hist)
    return 0;
  if (!hist->start_of_run || when < hist->start_of_run)
    return 0;
  return when - hist->start_of_run;
}
