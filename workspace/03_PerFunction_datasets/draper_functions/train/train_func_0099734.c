gmpc_log_func(
            const gchar * log_domain,
            GLogLevelFlags log_level,
            const gchar * message,
            gpointer user_data)
{
    if (log_level <= global_log_level)
    {
        g_log_default_handler(log_domain, log_level, message, user_data);
    }
}
