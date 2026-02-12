void manager_status_printf(Manager *m, bool ephemeral, const char *status, const char *format, ...) {
        va_list ap;

        if (!manager_get_show_status(m))
                return;


        if (ephemeral && m->n_on_console > 0)
                return;

        if (!manager_is_booting_or_shutting_down(m))
                return;

        va_start(ap, format);
        status_vprintf(status, true, ephemeral, format, ap);
        va_end(ap);
}
