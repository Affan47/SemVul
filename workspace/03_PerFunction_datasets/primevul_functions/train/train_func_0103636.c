mysql_declare_plugin(audit_null)
{
  MYSQL_AUDIT_PLUGIN,
  &audit_null_descriptor,
  "NULL_AUDIT",
  "Oracle Corp",
  "Simple NULL Audit",
  PLUGIN_LICENSE_GPL,
  audit_null_plugin_init,
  audit_null_plugin_deinit,
  0x0003,
  simple_status,
  system_variables,
  NULL,
  0,
}
