usage (int argc, char *argv[])
{
  GError *error;

  error = NULL;
  if (!g_spawn_command_line_sync ("man pkttyagent",
                                  NULL,
                                  NULL,
                                  NULL,
                                  &error))
    {
      g_printerr ("Cannot show manual page: %s (%s, %d)\n",
                  error->message, g_quark_to_string (error->domain), error->code);
      g_error_free (error);
    }
}
