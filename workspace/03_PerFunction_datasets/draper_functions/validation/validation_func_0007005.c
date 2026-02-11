lcrt_toolbar_create_config(struct lcrt_toolbar *ltoolbar)
{
    int i;
    if (ltoolbar == NULL)
        return EINVAL;
    ltoolbar->config.db.exec(&ltoolbar->config.db,
                         "CREATE TABLE %s( \
                          name VARCHAR(64) PRIMARY KEY, \
                          value VARCHAR(255))",
                         ltoolbar->get_tb(ltoolbar));
    for (i = 0; i < LCRT_B_NUMBER; i++) {
        ltoolbar->config.db.exec(&ltoolbar->config.db,
                             "INSERT INTO %s VALUES('%s', '%s')",
                             ltoolbar->get_tb(ltoolbar),
                             ltoolbar->config.name[i],
                             ltoolbar->config.value[i]);
    }
    ltoolbar->config.db.close(&ltoolbar->config.db);
    return 0;
}
