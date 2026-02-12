static void test_wl6587()
{
  int rc;
  MYSQL *l_mysql;
  my_bool can;

  myheader("test_wl6587");


  rc= mysql_query(mysql,
                  "CREATE USER wl6587_cli@localhost IDENTIFIED BY 'wl6587'");
  myquery(rc);
  rc= mysql_query(mysql, "ALTER USER wl6587_cli@localhost PASSWORD EXPIRE");
  myquery(rc);


  l_mysql= mysql_client_init(NULL);
  DIE_UNLESS(l_mysql != NULL);


  l_mysql= mysql_real_connect(l_mysql, opt_host, "wl6587_cli",
                              "wl6587", "test", opt_port,
                              opt_unix_socket, 0);
  DIE_UNLESS(l_mysql == 0);

  l_mysql= mysql_client_init(NULL);
  DIE_UNLESS(l_mysql != NULL);


  l_mysql= mysql_real_connect(l_mysql, opt_host, "wl6587_cli",
                         "wl6587", "test", opt_port,
                         opt_unix_socket,
                         CLIENT_CAN_HANDLE_EXPIRED_PASSWORDS);
  DIE_UNLESS(l_mysql != 0);


  rc= mysql_query(l_mysql, "SELECT USER()");
  myerror2(l_mysql,NULL);
  DIE_UNLESS(rc != 0);

  mysql_close(l_mysql);


  l_mysql= mysql_client_init(NULL);
  DIE_UNLESS(l_mysql != NULL);

  can= TRUE;
  rc= mysql_options(l_mysql, MYSQL_OPT_CAN_HANDLE_EXPIRED_PASSWORDS, &can);
  DIE_UNLESS(rc == 0);

  l_mysql= mysql_real_connect(l_mysql, opt_host, "wl6587_cli",
                         "wl6587", "test", opt_port,
                         opt_unix_socket, 0);
  DIE_UNLESS(l_mysql != 0);


  rc= mysql_query(l_mysql, "SELECT USER()");
  myerror2(l_mysql,NULL);
  DIE_UNLESS(rc != 0);

  mysql_close(l_mysql);


  l_mysql= mysql_client_init(NULL);
  DIE_UNLESS(l_mysql != NULL);

  can= FALSE;
  rc= mysql_options(l_mysql, MYSQL_OPT_CAN_HANDLE_EXPIRED_PASSWORDS, &can);
  DIE_UNLESS(rc == 0);


  l_mysql= mysql_real_connect(l_mysql, opt_host, opt_user,
                         opt_password, current_db, opt_port,
                         opt_unix_socket, 0);
  DIE_UNLESS(l_mysql != 0);

  rc= mysql_change_user(l_mysql, "wl6587_cli", "wl6587", "test");
  DIE_UNLESS(rc == TRUE);

  mysql_close(l_mysql);


  rc= mysql_query(mysql, "DROP USER wl6587_cli@localhost");
  myquery(rc);
}
