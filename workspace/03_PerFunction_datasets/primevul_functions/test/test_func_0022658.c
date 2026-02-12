open_tables_check_upgradable_mdl(THD *thd, TABLE_LIST *tables_start,
                                 TABLE_LIST *tables_end, uint flags)
{
  TABLE_LIST *table;

  DBUG_ASSERT(thd->locked_tables_mode);

  for (table= tables_start; table && table != tables_end;
       table= table->next_global)
  {


    DBUG_ASSERT(table->mdl_request.type != MDL_SHARED_READ_ONLY);
    if (table->mdl_request.type < MDL_SHARED_UPGRADABLE ||
        table->open_type == OT_TEMPORARY_ONLY ||
        (table->open_type == OT_TEMPORARY_OR_BASE && is_temporary_table(table)))
    {
      continue;
    }


    if (!find_table_for_mdl_upgrade(thd, table->db, table->table_name, NULL))
      return TRUE;
  }

  return FALSE;
}
