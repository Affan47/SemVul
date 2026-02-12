receive_bomb_out(uschar *reason, uschar *msg)
{
  static BOOL already_bombing_out;


if (spool_name[0] != '\0')
  {
  Uunlink(spool_name);
  spool_name[Ustrlen(spool_name) - 1] = 'H';
  Uunlink(spool_name);
  spool_name[0] = '\0';
  }


if (data_file != NULL)
  {
  (void)fclose(data_file);
  data_file = NULL;
} else if (data_fd >= 0) {
  (void)close(data_fd);
  data_fd = -1;
  }


if (!already_bombing_out)
  {
  already_bombing_out = TRUE;
  if (smtp_input)
    {
    if (smtp_batched_input)
      moan_smtp_batch(NULL, "421 %s - message abandoned", msg);
    smtp_notquit_exit(reason, US"421", US"%s %s - closing connection.",
      smtp_active_hostname, msg);
    }
  }


exim_exit(EXIT_FAILURE, NULL);
}
