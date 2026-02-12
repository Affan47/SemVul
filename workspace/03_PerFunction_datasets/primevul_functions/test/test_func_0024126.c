static bool multi_update_check_table_access(THD *thd, TABLE_LIST *table,
                                            table_map tables_for_update,
                                            bool *updated_arg)
{
  if (table->view)
  {
    bool updated= false;


    DBUG_ASSERT(table->merge_underlying_list ||
                (!table->updatable &&
                 !(table->table->map & tables_for_update)));

    for (TABLE_LIST *tbl= table->merge_underlying_list; tbl;
         tbl= tbl->next_local)
    {
      if (multi_update_check_table_access(thd, tbl, tables_for_update,
                                          &updated))
      {
        tbl->hide_view_error(thd);
        return true;
      }
    }
    if (check_table_access(thd, updated ? UPDATE_ACL: SELECT_ACL, table,
                           FALSE, 1, FALSE))
      return true;
    *updated_arg|= updated;

    table->grant.want_privilege= SELECT_ACL & ~table->grant.privilege;
  }
  else
  {

    const bool updated= table->table->map & tables_for_update;
    if (check_table_access(thd, updated ? UPDATE_ACL : SELECT_ACL, table,
                           FALSE, 1, FALSE))
      return true;
    *updated_arg|= updated;

    if (!table->derived)
    {
      table->grant.want_privilege= SELECT_ACL & ~table->grant.privilege;
      table->table->grant.want_privilege= (SELECT_ACL &
                                           ~table->table->grant.privilege);
    }
  }
  return false;
}
