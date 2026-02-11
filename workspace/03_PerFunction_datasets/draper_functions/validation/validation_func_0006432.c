check_show_routine_access(THD *thd, sp_head *sp, bool *full_access)
{
  TABLE_LIST tables;
  bzero((char*) &tables,sizeof(tables));
  tables.db= (char*) "mysql";
  tables.table_name= tables.alias= (char*) "proc";
  *full_access= ((!check_table_access(thd, SELECT_ACL, &tables, FALSE,
                                     1, TRUE) &&
                  (tables.grant.privilege & SELECT_ACL) != 0) ||
                 (!strcmp(sp->m_definer_user.str,
                          thd->security_ctx->priv_user) &&
                  !strcmp(sp->m_definer_host.str,
                          thd->security_ctx->priv_host)));
  if (!*full_access)
    return check_some_routine_access(thd, sp->m_db.str, sp->m_name.str,
                                     sp->m_type == TYPE_ENUM_PROCEDURE);
  return 0;
}
