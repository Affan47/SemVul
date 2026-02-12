static void sst_disallow_writes(THD *thd, bool yes) {


  char query_str[128] = {
      0,
  };
  ssize_t const query_max = sizeof(query_str) - 1;
  snprintf(query_str, query_max, "SET GLOBAL innodb_disallow_writes=%s",
           yes ? "true" : "false");

  if (run_sql_command(thd, query_str, NULL)) {
    WSREP_ERROR("Failed to disallow InnoDB writes");
  }
  return;
}
