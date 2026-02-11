log_argv(ObDebugType type,
                            const gchar *format, va_list args)
{
    const gchar *prefix;
    gchar *message;

    g_assert(type < OB_DEBUG_TYPE_NUM);
    if (!enabled_types[type]) return;

    switch (type) {
    case OB_DEBUG_FOCUS:    prefix = "(FOCUS) ";           break;
    case OB_DEBUG_APP_BUGS: prefix = "(APPLICATION BUG) "; break;
    case OB_DEBUG_SM:       prefix = "(SESSION) ";         break;
    default:                prefix = NULL;                 break;
    }

    message = g_strdup_vprintf(format, args);
    if (prefix) {
        gchar *a = message;
        message = g_strconcat(prefix, message, NULL);
        g_free(a);
    }

    g_debug("%s", message);
    g_free(message);
}
