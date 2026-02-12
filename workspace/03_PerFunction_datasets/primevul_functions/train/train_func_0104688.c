void manager_status_printf(Manager *m, StatusType type, const char *status, const char *format, ...) {
        va_list ap;


        if (m && !manager_get_show_status(m, type))
                return;


        if (type == STATUS_TYPE_EPHEMERAL && m && m->n_on_console > 0)
                return;

        va_start(ap, format);
        status_vprintf(status, true, type == STATUS_TYPE_EPHEMERAL, format, ap);
        va_end(ap);
}
