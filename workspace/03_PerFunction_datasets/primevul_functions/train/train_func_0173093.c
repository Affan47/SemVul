void redirect_to_syslog(void) {
   static int has_inited = 0;


   if (!has_inited) {
#ifdef OS_UNIX
      setlogmask(LOG_UPTO(SYSLOG_PRIORITY));
      openlog("elogd", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
#else
      hEventLog = RegisterEventSource(NULL, "ELOG");
#endif
   }
   has_inited = 1;

   printf_handler = print_syslog;
   fputs_handler = fputs_syslog;


   current_output_stream = NULL;
}
