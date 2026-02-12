bool mysql_user_password_expire(THD *thd, List <LEX_USER> &list)
{
  bool result= false;
  String wrong_users;
  LEX_USER *user_from, *tmp_user_from;
  List_iterator <LEX_USER> user_list(list);
  TABLE_LIST tables;
  TABLE *table;
  bool some_passwords_expired= false;
  bool save_binlog_row_based;
  DBUG_ENTER("mysql_user_password_expire");

  if (!initialized)
  {
    my_error(ER_OPTION_PREVENTS_STATEMENT, MYF(0), "--skip-grant-tables");
    DBUG_RETURN(true);
  }
  tables.init_one_table("mysql", 5, "user", 4, "user", TL_WRITE);

#ifdef HAVE_REPLICATION


  if (thd->slave_thread && rpl_filter->is_on())
  {


    tables.updating= 1;

    if (!(thd->sp_runtime_ctx || rpl_filter->tables_ok(0, &tables)))
      DBUG_RETURN(false);
  }
#endif
  if (!(table= open_ltable(thd, &tables, TL_WRITE, MYSQL_LOCK_IGNORE_TIMEOUT)))
    DBUG_RETURN(true);

  if (!table->key_info)
  {
    my_error(ER_TABLE_CORRUPT, MYF(0), table->s->db.str,
             table->s->table_name.str);
    DBUG_RETURN(true);
  }


  if ((save_binlog_row_based= thd->is_current_stmt_binlog_format_row()))
    thd->clear_current_stmt_binlog_format_row();

  mysql_rwlock_wrlock(&LOCK_grant);
  mysql_mutex_lock(&acl_cache->lock);

  while ((tmp_user_from= user_list++))
  {
    ACL_USER *acl_user;


    if (!(user_from= get_current_user(thd, tmp_user_from)))
    {
      result= true;
      append_user(thd, &wrong_users, tmp_user_from, wrong_users.length() > 0,
                  false);
      continue;
    }


    if (!(acl_user= find_acl_user(user_from->host.str,
                                   user_from->user.str, TRUE)))
    {
      result= true;
      append_user(thd, &wrong_users, user_from, wrong_users.length() > 0,
                  false);
      continue;
    }


    if (!auth_plugin_supports_expiration(acl_user->plugin.str))
    {
      result= true;
      append_user(thd, &wrong_users, user_from, wrong_users.length() > 0,
                  false);
      continue;
    }


    enum mysql_user_table_field password_field= MYSQL_USER_FIELD_PASSWORD;
    if (update_user_table(thd, table,
                          acl_user->host.get_host() ?
                          acl_user->host.get_host() : "",
                          acl_user->user ? acl_user->user : "",
                          NULL, 0, password_field, true, false))
    {
      result= true;
      append_user(thd, &wrong_users, user_from, wrong_users.length() > 0,
                  false);
      continue;
    }

    acl_user->password_expired= true;
    some_passwords_expired= true;
  }

  acl_cache->clear(1);
  mysql_mutex_unlock(&acl_cache->lock);

  if (result)
    my_error(ER_CANNOT_USER, MYF(0), "ALTER USER", wrong_users.c_ptr_safe());

  if (!result && some_passwords_expired)
  {
    const char *query= thd->rewritten_query.length() ?
      thd->rewritten_query.c_ptr_safe() : thd->query();
    const size_t query_length= thd->rewritten_query.length() ?
      thd->rewritten_query.length() : thd->query_length();
    result= (write_bin_log(thd, false, query, query_length,
                           table->file->has_transactions()) != 0);
  }

  mysql_rwlock_unlock(&LOCK_grant);

  result|= acl_trans_commit_and_close_tables(thd);


  DBUG_ASSERT(!thd->is_current_stmt_binlog_format_row());
  if (save_binlog_row_based)
    thd->set_current_stmt_binlog_format_row();
  DBUG_RETURN(result);
}
