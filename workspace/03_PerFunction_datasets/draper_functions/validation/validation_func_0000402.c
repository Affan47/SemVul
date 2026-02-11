io_watch_have_data (GIOChannel    *channel,
                    GIOCondition   condition,
                    gpointer       user_data)
{
  PolkitAgentSession *session = POLKIT_AGENT_SESSION (user_data);
  gchar *line, *unescaped;
  GError *error;

  error = NULL;
  line = NULL;
  unescaped = NULL;

  if (!session->helper_is_running)
    {
      g_warning ("in io_watch_have_data() but helper is not supposed to be running");

      complete_session (session, FALSE);
      goto out;
    }

  g_io_channel_read_line (channel,
                          &line,
                          NULL,
                          NULL,
                          &error);
  if (error != NULL)
    {
      g_warning ("Error reading line from helper: %s", error->message);
      g_error_free (error);

      complete_session (session, FALSE);
      goto out;
    }


  if (strlen (line) > 0 && line[strlen (line) - 1] == '\n')
    line[strlen (line) - 1] = '\0';

  unescaped = g_strcompress (line);

  if (G_UNLIKELY (_show_debug ()))
    g_print ("PolkitAgentSession: read `%s' from helper\n", unescaped);

  if (g_str_has_prefix (unescaped, "PAM_PROMPT_ECHO_OFF "))
    {
      const gchar *s = unescaped + sizeof "PAM_PROMPT_ECHO_OFF " - 1;
      if (G_UNLIKELY (_show_debug ()))
        g_print ("PolkitAgentSession: emitting ::request('%s', FALSE)\n", s);
      g_signal_emit_by_name (session, "request", s, FALSE);
    }
  else if (g_str_has_prefix (unescaped, "PAM_PROMPT_ECHO_ON "))
    {
      const gchar *s = unescaped + sizeof "PAM_PROMPT_ECHO_ON " - 1;
      if (G_UNLIKELY (_show_debug ()))
        g_print ("PolkitAgentSession: emitting ::request('%s', TRUE)\n", s);
      g_signal_emit_by_name (session, "request", s, TRUE);
    }
  else if (g_str_has_prefix (unescaped, "PAM_ERROR_MSG "))
    {
      const gchar *s = unescaped + sizeof "PAM_ERROR_MSG " - 1;
      if (G_UNLIKELY (_show_debug ()))
        g_print ("PolkitAgentSession: emitting ::show-error('%s')\n", s);
      g_signal_emit_by_name (session, "show-error", s);
    }
  else if (g_str_has_prefix (unescaped, "PAM_TEXT_INFO "))
    {
      const gchar *s = unescaped + sizeof "PAM_TEXT_INFO " - 1;
      if (G_UNLIKELY (_show_debug ()))
        g_print ("PolkitAgentSession: emitting ::show-info('%s')\n", s);
      g_signal_emit_by_name (session, "show-info", s);
    }
  else if (g_str_has_prefix (unescaped, "SUCCESS"))
    {
      complete_session (session, TRUE);
    }
  else if (g_str_has_prefix (unescaped, "FAILURE"))
    {
      complete_session (session, FALSE);
    }
  else
    {
      g_warning ("Unknown line '%s' from helper", line);
      complete_session (session, FALSE);
      goto out;
    }

 out:
  g_free (line);
  g_free (unescaped);


  return TRUE;
}
