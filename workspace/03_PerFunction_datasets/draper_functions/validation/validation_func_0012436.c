ck_job_execute (CkJob   *job,
                GError **error)
{
        GError     *local_error;
        gboolean    res;
        GIOChannel *channel;
        int         standard_output;
        int         standard_error;
        int         argc;
        char      **argv;

        g_debug ("Executing %s", job->priv->command);
        local_error = NULL;
        if (! g_shell_parse_argv (job->priv->command, &argc, &argv, &local_error)) {
                g_debug ("Could not parse command: %s", local_error->message);
                g_propagate_error (error, local_error);
                return FALSE;
        }

        local_error = NULL;
        res = g_spawn_async_with_pipes (NULL,
                                        argv,
                                        NULL,
                                        G_SPAWN_DO_NOT_REAP_CHILD,
                                        NULL,
                                        NULL,
                                        &job->priv->child_pid,
                                        NULL,
                                        &standard_output,
                                        &standard_error,
                                        &local_error);

        g_strfreev (argv);
        if (! res) {
                g_debug ("Could not start command '%s': %s",
                          job->priv->command,
                          local_error->message);
                g_propagate_error (error, local_error);
                return FALSE;
        }


        channel = g_io_channel_unix_new (standard_output);
        g_io_channel_set_close_on_unref (channel, TRUE);
        g_io_channel_set_flags (channel,
                                g_io_channel_get_flags (channel) | G_IO_FLAG_NONBLOCK,
                                NULL);
        job->priv->out_watch_id = g_io_add_watch (channel,
                                                  G_IO_IN | G_IO_HUP | G_IO_ERR | G_IO_NVAL,
                                                  (GIOFunc)out_watch,
                                                  job);
        g_io_channel_unref (channel);


        channel = g_io_channel_unix_new (standard_error);
        g_io_channel_set_close_on_unref (channel, TRUE);
        g_io_channel_set_flags (channel,
                                g_io_channel_get_flags (channel) | G_IO_FLAG_NONBLOCK,
                                NULL);
        job->priv->err_watch_id = g_io_add_watch (channel,
                                                  G_IO_IN | G_IO_HUP | G_IO_ERR | G_IO_NVAL,
                                                  (GIOFunc)error_watch,
                                                  job);
        g_io_channel_unref (channel);

        return res;
}
