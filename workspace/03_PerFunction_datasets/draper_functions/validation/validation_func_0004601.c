lcrt_config_exec(struct lcrt_config *config, const char *format, ...)
{
    int rv;
    char sql[4096];
    va_list args;

    if (config == NULL || (rv = config->open(config)) != 0)
        return rv;

    debug_where();
     va_start(args, format);
     vsprintf(sql, format, args);
     va_end(args);

     config->db_rv = sqlite3_exec(config->db, sql, 0, 0, NULL);
     if (config->db_rv != SQLITE_OK)
         return EIO;
     return LCRTE_OK;
}
