static int manager_default_environment(Manager *m) {
        assert(m);

        if (MANAGER_IS_SYSTEM(m)) {


                m->environment = strv_new("PATH=" DEFAULT_PATH,
                                          NULL);


                locale_setup(&m->environment);
        } else {


                m->environment = strv_copy(environ);
        }

        if (!m->environment)
                return -ENOMEM;

        manager_clean_environment(m);
        strv_sort(m->environment);

        return 0;
}
