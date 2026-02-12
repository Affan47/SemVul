static bool manager_get_show_status(Manager *m) {
        assert(m);

        if (m->running_as != SYSTEMD_SYSTEM)
                return false;

        if (m->no_console_output)
                return false;

        if (m->show_status > 0)
                return true;


        return plymouth_running();
}
