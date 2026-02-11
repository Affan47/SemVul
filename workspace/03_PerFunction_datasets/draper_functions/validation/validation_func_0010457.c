log_to (int mask)
{
  if (logto & LOGTO_SYSLOG)
    closelog ();

  logto = mask;

  if (logto & LOGTO_SYSLOG)
    openlog (log_identity, LOG_CONS | LOG_PID, LOG_DAEMON);
}
