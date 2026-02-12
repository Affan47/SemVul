gboolean session_info_session_is_locked(struct session_info *info)
{
    gboolean locked;

    g_return_val_if_fail (info != NULL, FALSE);


    si_dbus_read_signals(info);
    locked = info->session_idle_hint;
    if (info->verbose) {
        syslog(LOG_DEBUG, "(console-kit) session is locked: %s",
               locked ? "yes" : "no");
    }
    return locked;
}
