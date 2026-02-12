close_unwanted(void)
{
if (smtp_input)
  {
#ifdef SUPPORT_TLS
  tls_close(NULL, TLS_NO_SHUTDOWN);
#endif
  (void)close(fileno(smtp_in));
  (void)close(fileno(smtp_out));
  smtp_in = NULL;
  }
else
  {
  (void)close(0);
  if ((debug_selector & D_resolver) == 0) (void)close(1);
  if (debug_selector == 0)
    {
    if (!f.synchronous_delivery)
      {
      (void)close(2);
      log_stderr = NULL;
      }
    (void)setsid();
    }
  }
}
