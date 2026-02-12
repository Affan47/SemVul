my_bool	STDCALL mysql_change_user(MYSQL *mysql, const char *user,
				  const char *passwd, const char *db)
{
  int rc;
  CHARSET_INFO *saved_cs= mysql->charset;
  char *saved_user= mysql->user;
  char *saved_passwd= mysql->passwd;
  char *saved_db= mysql->db;

  DBUG_ENTER("mysql_change_user");


  if (mysql_init_character_set(mysql))
  {
    mysql->charset= saved_cs;
    DBUG_RETURN(TRUE);
  }


  mysql->user= (char*)(user ? user : "");
  mysql->passwd= (char*)(passwd ? passwd : "");
  mysql->db= 0;

  rc= run_plugin_auth(mysql, 0, 0, 0, db);


  mysql_detach_stmt_list(&mysql->stmts, "mysql_change_user");
  if (rc == 0)
  {

    my_free(saved_user);
    my_free(saved_passwd);
    my_free(saved_db);


    mysql->user= my_strdup(mysql->user, MYF(MY_WME));
    mysql->passwd= my_strdup(mysql->passwd, MYF(MY_WME));
    mysql->db= db ? my_strdup(db, MYF(MY_WME)) : 0;
  }
  else
  {
    mysql->charset= saved_cs;
    mysql->user= saved_user;
    mysql->passwd= saved_passwd;
    mysql->db= saved_db;
  }

  DBUG_RETURN(rc);
}
