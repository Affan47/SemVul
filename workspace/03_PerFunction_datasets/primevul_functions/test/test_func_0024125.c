bool Multiupdate_prelocking_strategy::handle_end(THD *thd)
{
  DBUG_ENTER("Multiupdate_prelocking_strategy::handle_end");
  if (done)
    DBUG_RETURN(0);

  LEX *lex= thd->lex;
  SELECT_LEX *select_lex= &lex->select_lex;
  TABLE_LIST *table_list= lex->query_tables, *tl;

  done= true;

  if (mysql_handle_derived(lex, DT_INIT) ||
      mysql_handle_derived(lex, DT_MERGE_FOR_INSERT) ||
      mysql_handle_derived(lex, DT_PREPARE))
    DBUG_RETURN(1);


  if (setup_tables_and_check_access(thd, &select_lex->context,
      &select_lex->top_join_list, table_list, select_lex->leaf_tables,
      FALSE, UPDATE_ACL, SELECT_ACL, TRUE))
    DBUG_RETURN(1);

  List<Item> *fields= &lex->select_lex.item_list;
  if (setup_fields_with_no_wrap(thd, Ref_ptr_array(),
                                *fields, MARK_COLUMNS_WRITE, 0, 0))
    DBUG_RETURN(1);


  for (tl= table_list; tl ; tl= tl->next_local)
    if (tl->view)
      break;

  if (check_fields(thd, *fields, tl != NULL ))
    DBUG_RETURN(1);

  table_map tables_for_update= thd->table_map_for_update= get_table_map(fields);

  if (unsafe_key_update(select_lex->leaf_tables, tables_for_update))
    DBUG_RETURN(1);


  List_iterator<TABLE_LIST> ti(select_lex->leaf_tables);
  const bool using_lock_tables= thd->locked_tables_mode != LTM_NONE;
  while ((tl= ti++))
  {
    TABLE *table= tl->table;

    if (tl->is_jtbm())
      continue;


    if (table->map & tables_for_update)
    {
      if (!tl->single_table_updatable() || check_key_in_view(thd, tl))
      {
        my_error(ER_NON_UPDATABLE_TABLE, MYF(0),
                 tl->top_table()->alias.str, "UPDATE");
        DBUG_RETURN(1);
      }

      DBUG_PRINT("info",("setting table `%s` for update",
                         tl->top_table()->alias.str));


      tl->updating= 1;
      if (tl->belong_to_view)
        tl->belong_to_view->updating= 1;
      if (extend_table_list(thd, tl, this, has_prelocking_list))
        DBUG_RETURN(1);
    }
    else
    {
      DBUG_PRINT("info",("setting table `%s` for read-only", tl->alias.str));


      DBUG_ASSERT(tl->prelocking_placeholder == false);
      thr_lock_type lock_type= read_lock_type_for_table(thd, lex, tl, true);
      if (using_lock_tables)
        tl->lock_type= lock_type;
      else
        tl->set_lock_type(thd, lock_type);
    }
  }


  for (tl= table_list; tl; tl= tl->next_local)
  {
    bool not_used= false;
    if (tl->is_jtbm())
      continue;
    if (multi_update_check_table_access(thd, tl, tables_for_update, &not_used))
      DBUG_RETURN(TRUE);
  }


  for (tl= table_list; tl; tl= tl->next_local)
  {
    TABLE_LIST *for_update= 0;
    if (tl->is_jtbm())
      continue;
    if (tl->is_merged_derived() &&
        tl->check_single_table(&for_update, tables_for_update, tl))
    {
      my_error(ER_VIEW_MULTIUPDATE, MYF(0), tl->view_db.str, tl->view_name.str);
      DBUG_RETURN(1);
    }
  }

  DBUG_RETURN(0);
}
