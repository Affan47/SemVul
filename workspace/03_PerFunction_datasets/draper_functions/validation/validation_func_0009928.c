get_erase_duration_string (gint minutes)
{
  gchar *s;
  if (minutes == 510)
    {
      gchar *s2 = gdu_utils_format_duration_usec ((minutes - 2) * 60LL * G_USEC_PER_SEC,
                                                  GDU_FORMAT_DURATION_FLAGS_NONE);


      s = g_strdup_printf (_("At least %s"), s2);
      g_free (s2);
    }
  else
    {
      gchar *s2 = gdu_utils_format_duration_usec (minutes * 60LL * G_USEC_PER_SEC,
                                                  GDU_FORMAT_DURATION_FLAGS_NONE);


      s = g_strdup_printf (_("Approximately %s"), s2);
      g_free (s2);
    }
  return s;
}
