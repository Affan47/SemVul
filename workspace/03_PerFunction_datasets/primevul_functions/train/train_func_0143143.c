static int wsrep_create_sst_user(bool initialize_thread, const char *password) {
  int err = 0;
  int const auth_len = 512;
  char auth_buf[auth_len];
  MYSQL_SESSION session = NULL;


  const char *cmds[] = {
    "SET SESSION sql_log_bin = OFF;",
    nullptr,
    "DROP USER IF EXISTS 'mysql.pxc.sst.user'@localhost;",
    nullptr,
    "CREATE USER 'mysql.pxc.sst.user'@localhost "
    " IDENTIFIED BY '%s' ACCOUNT LOCK;",
    "CREATE USER mysql.pxc.sst.user IDENTIFIED WITH * BY * ACCOUNT LOCK",


#if 0
    "GRANT 'mysql.pxc.sst.role'@localhost TO 'mysql.pxc.sst.user'@localhost;", nullptr,
    "SET DEFAULT ROLE 'mysql.pxc.sst.role'@localhost to 'mysql.pxc.sst.user'@localhost;", nullptr,
#else


    "GRANT BACKUP_ADMIN, LOCK TABLES, PROCESS, RELOAD, REPLICATION CLIENT, "
    "SUPER ON *.* TO 'mysql.pxc.sst.user'@localhost;",
    nullptr,
    "GRANT CREATE, INSERT, SELECT ON PERCONA_SCHEMA.xtrabackup_history TO "
    "'mysql.pxc.sst.user'@localhost;",
    nullptr,
    "GRANT SELECT ON performance_schema.* TO 'mysql.pxc.sst.user'@localhost;",
    nullptr,
    "GRANT CREATE USER ON *.* to 'mysql.pxc.sst.user'@localhost;",
    nullptr,
    "GRANT CREATE ON PERCONA_SCHEMA.* to 'mysql.pxc.sst.user'@localhost;",
    nullptr,
#endif

    "ALTER USER 'mysql.pxc.sst.user'@localhost ACCOUNT UNLOCK;",
    nullptr,
    nullptr,
    nullptr
  };

  wsrep_allow_server_session = true;
  session = setup_server_session(initialize_thread);
  if (!session) {
    wsrep_allow_server_session = false;
    return ECANCELED;
  }

  for (int index = 0; !err && cmds[index]; index += 2) {
    int ret;
    ret = snprintf(auth_buf, auth_len, cmds[index], password);
    if (ret < 0 || ret >= auth_len) {
      WSREP_ERROR("wsrep_create_sst_user() : snprintf() failed: %d", ret);
      err = (ret < 0 ? ret : -EMSGSIZE);
      break;
    }

    err = server_session_execute(session, auth_buf, cmds[index + 1], true);
  }


  ::memset(auth_buf, 0, auth_len);

  cleanup_server_session(session, initialize_thread);
  wsrep_allow_server_session = false;
  return err;
}
