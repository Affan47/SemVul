is_not_initialized(MYSQL *mysql, const char *name)
{
  if (initialized)
    return 0;

  set_mysql_extended_error(mysql, CR_AUTH_PLUGIN_CANNOT_LOAD,
                           unknown_sqlstate, ER(CR_AUTH_PLUGIN_CANNOT_LOAD),
                           name, "not initialized");
  return 1;
}
