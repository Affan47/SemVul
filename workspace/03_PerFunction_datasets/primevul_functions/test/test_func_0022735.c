TABLE_LIST* find_dup_table(THD *thd, TABLE_LIST *table, TABLE_LIST *table_list,
                           uint check_flag)
{
  TABLE_LIST *res= 0;
  const char *d_name, *t_name, *t_alias;
  DBUG_ENTER("find_dup_table");
  DBUG_PRINT("enter", ("table alias: %s", table->alias));


  if (table->table)
  {

    DBUG_ASSERT(table->table->file->ht->db_type != DB_TYPE_MRG_MYISAM);

    table= table->find_underlying_table(table->table);


    DBUG_ASSERT(table);
  }
  d_name= table->db;
  t_name= table->table_name;
  t_alias= table->alias;

retry:
  DBUG_PRINT("info", ("real table: %s.%s", d_name, t_name));
  for (TABLE_LIST *tl= table_list; tl ; tl= tl->next_global, res= 0)
  {
    if (tl->select_lex && tl->select_lex->master_unit() &&
        tl->select_lex->master_unit()->executed)
    {


      continue;
    }


    if (! (res= find_table_in_global_list(tl, d_name, t_name)))
      break;
    tl= res;


    if (res->table && (res->table == table->table))
      continue;


    if (check_flag & CHECK_DUP_SKIP_TEMP_TABLE &&
        res->table && res->table->s->tmp_table != NO_TMP_TABLE)
    {
      continue;
    }
    if (check_flag & CHECK_DUP_FOR_CREATE)
      DBUG_RETURN(res);


    if (check_flag & CHECK_DUP_ALLOW_DIFFERENT_ALIAS)
    {
      if (my_strcasecmp(table_alias_charset, t_alias, res->alias))
        continue;
    }


    if (res->select_lex &&
        !res->select_lex->exclude_from_table_unique_test &&
        !res->prelocking_placeholder)
      break;


    DBUG_PRINT("info",
               ("found same copy of table or table which we should skip"));
  }
  if (res && res->belong_to_derived)
  {


    TABLE_LIST *derived=  res->belong_to_derived;
    if (derived->is_merged_derived() && !derived->derived->is_excluded())
    {
      DBUG_PRINT("info",
                 ("convert merged to materialization to resolve the conflict"));
      derived->change_refs_to_fields();
      derived->set_materialized_derived();
      goto retry;
    }
  }
  DBUG_RETURN(res);
}
