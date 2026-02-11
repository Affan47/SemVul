getpw_log(log_level_t level, char *fmt, ...)
{
  char buffer[80];
  struct tm now_tm;
  time_t now_time;
  va_list ap;

  if ( level <= LOG_TRACE ) return;

  time(&now_time);
  localtime_r(&now_time, &now_tm);
  strftime(&buffer[0], 80, "%H:%M:%S, %a, %b %d %Y: ", &now_tm);
  printf("%s", buffer);
  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
  puts("");
}
