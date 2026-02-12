int wsrep_remove_sst_user(bool initialize_thread) {
  int err = 0;
  MYSQL_SESSION session = NULL;


  if (skip_grant_tables()) {
    return ECANCELED;
  }


  const char *cmds[] = {"SET SESSION sql_log_bin = OFF;",
                        nullptr,
                        "SET SESSION lock_wait_timeout = 1;",
                        nullptr,
                        "DROP USER IF EXISTS 'mysql.pxc.sst.user'@localhost;",
                        nullptr,
                        nullptr,
                        nullptr};

  wsrep_allow_server_session = true;
  session = setup_server_session(initialize_thread);
  if (!session) {
    wsrep_allow_server_session = false;
    return ECANCELED;
  }

  for (int index = 0; !err && cmds[index]; index += 2) {

    err = server_session_execute(session, cmds[index], cmds[index + 1], true);
  }

  cleanup_server_session(session, initialize_thread);
  wsrep_allow_server_session = false;
  return err;
}
