find_field_in_tables(THD *thd, Item_ident *item,
                     TABLE_LIST *first_table, TABLE_LIST *last_table,
		     Item **ref, find_item_error_report_type report_error,
                     bool check_privileges, bool register_tree_change)
{
  Field *found=0;
  const char *db= item->db_name;
  const char *table_name= item->table_name;
  const char *name= item->field_name;
  uint length=(uint) strlen(name);
  char name_buff[SAFE_NAME_LEN+1];
  TABLE_LIST *cur_table= first_table;
  TABLE_LIST *actual_table;
  bool allow_rowid;

  if (!table_name || !table_name[0])
  {
    table_name= 0;
    db= 0;
  }

  allow_rowid= table_name || (cur_table && !cur_table->next_local);

  if (item->cached_table)
  {
    DBUG_PRINT("info", ("using cached table"));


    TABLE_LIST *table_ref= item->cached_table;


    if (table_ref->table && !table_ref->view &&
        (!table_ref->is_merged_derived() ||
         (!table_ref->is_multitable() && table_ref->merged_for_insert)))
    {

      found= find_field_in_table(thd, table_ref->table, name, length,
                                 TRUE, &(item->cached_field_index));
#ifndef NO_EMBEDDED_ACCESS_CHECKS

      if (found && check_privileges && !is_temporary_table(table_ref) &&
          check_column_grant_in_table_ref(thd, table_ref, name, length))
        found= WRONG_GRANT;
#endif
    }
    else
      found= find_field_in_table_ref(thd, table_ref, name, length, item->name,
                                     NULL, NULL, ref, check_privileges,
                                     TRUE, &(item->cached_field_index),
                                     register_tree_change,
                                     &actual_table);
    if (found)
    {
      if (found == WRONG_GRANT)
	return (Field*) 0;


      if (!table_ref->belong_to_view &&
          !table_ref->belong_to_derived)
      {
        SELECT_LEX *current_sel= item->context->select_lex;
        SELECT_LEX *last_select= table_ref->select_lex;
        bool all_merged= TRUE;
        for (SELECT_LEX *sl= current_sel; sl && sl!=last_select;
             sl=sl->outer_select())
        {
          Item *subs= sl->master_unit()->item;
          if (!subs ||
              (subs->type() == Item::SUBSELECT_ITEM &&
               ((Item_subselect*)subs)->substype() == Item_subselect::IN_SUBS &&
               ((Item_in_subselect*)subs)->test_strategy(SUBS_SEMI_JOIN)))
          {
            continue;
          }
          all_merged= FALSE;
          break;
        }


        if (!all_merged && current_sel != last_select)
        {
          mark_select_range_as_dependent(thd, last_select, current_sel,
                                         found, *ref, item, true);
        }
      }
      return found;
    }
  }
  else
    item->can_be_depended= TRUE;

  if (db && lower_case_table_names)
  {


    strmake_buf(name_buff, db);
    my_casedn_str(files_charset_info, name_buff);
    db= name_buff;
  }

  if (last_table)
    last_table= last_table->next_name_resolution_table;

  for (; cur_table != last_table ;
       cur_table= cur_table->next_name_resolution_table)
  {
    Field *cur_field= find_field_in_table_ref(thd, cur_table, name, length,
                                              item->name, db, table_name, ref,
                                              (thd->lex->sql_command ==
                                               SQLCOM_SHOW_FIELDS)
                                              ? false : check_privileges,
                                              allow_rowid,
                                              &(item->cached_field_index),
                                              register_tree_change,
                                              &actual_table);
    if (cur_field)
    {
      if (cur_field == WRONG_GRANT)
      {
        if (thd->lex->sql_command != SQLCOM_SHOW_FIELDS)
          return (Field*) 0;

        thd->clear_error();
        cur_field= find_field_in_table_ref(thd, cur_table, name, length,
                                           item->name, db, table_name, ref,
                                           false,
                                           allow_rowid,
                                           &(item->cached_field_index),
                                           register_tree_change,
                                           &actual_table);
        if (cur_field)
        {
          Field *nf=new Field_null(NULL,0,Field::NONE,
                                   cur_field->field_name,
                                   &my_charset_bin);
          nf->init(cur_table->table);
          cur_field= nf;
        }
      }


      item->cached_table= (!actual_table->cacheable_table || found) ?
                          0 : actual_table;

      DBUG_ASSERT(thd->where);


      if (db)
        return cur_field;

      if (found)
      {
        if (report_error == REPORT_ALL_ERRORS ||
            report_error == IGNORE_EXCEPT_NON_UNIQUE)
          my_error(ER_NON_UNIQ_ERROR, MYF(0),
                   table_name ? item->full_name() : name, thd->where);
        return (Field*) 0;
      }
      found= cur_field;
    }
  }

  if (found)
    return found;


  if (table_name && (cur_table == first_table) &&
      (report_error == REPORT_ALL_ERRORS ||
       report_error == REPORT_EXCEPT_NON_UNIQUE))
  {
    char buff[SAFE_NAME_LEN*2 + 2];
    if (db && db[0])
    {
      strxnmov(buff,sizeof(buff)-1,db,".",table_name,NullS);
      table_name=buff;
    }
    my_error(ER_UNKNOWN_TABLE, MYF(0), table_name, thd->where);
  }
  else
  {
    if (report_error == REPORT_ALL_ERRORS ||
        report_error == REPORT_EXCEPT_NON_UNIQUE)
      my_error(ER_BAD_FIELD_ERROR, MYF(0), item->full_name(), thd->where);
    else
      found= not_found_field;
  }
  return found;
}
