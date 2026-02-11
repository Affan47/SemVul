gftpui_common_clear_show_subhelp (const char *topic)
{
  if (strcmp (topic, "cache") == 0)
    {
      gftpui_common_logfunc (gftp_logging_misc, NULL,
                             _("Clear the directory cache\n"));
      return (1);
    }

  return (0);
}
