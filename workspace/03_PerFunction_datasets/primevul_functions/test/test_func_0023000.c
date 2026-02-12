maria_declare_plugin(aria)
{
  MYSQL_STORAGE_ENGINE_PLUGIN,
  &maria_storage_engine,
  "Aria",
  "MariaDB Corporation Ab",
  "Crash-safe tables with MyISAM heritage. Used for internal temporary tables and privilege tables",
  PLUGIN_LICENSE_GPL,
  ha_maria_init,
  NULL,
  0x0105,
  status_variables,
  system_variables,
  "1.5",
  MariaDB_PLUGIN_MATURITY_STABLE
}
