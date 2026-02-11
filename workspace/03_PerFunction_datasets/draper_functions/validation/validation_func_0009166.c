get_tz_offset(void)
{
  time_t now = current_time();
  time_t later = mktime(gmtime(&now));

  if (later == -1) {
    return 0;
  } else {
    return (signed int) difftime(now, later);
  }
}
