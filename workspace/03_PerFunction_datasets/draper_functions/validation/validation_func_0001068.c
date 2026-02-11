log_init(const char *process_name)
{

  if (!EmptyString(process_name))
    logInfo.procname = process_name;


  openlog(logInfo.procname, LOG_PID | LOG_NDELAY, logInfo.facility);
}
