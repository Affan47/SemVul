insert_fields(THD *thd, Name_resolution_context *context, const char *db_name,
	      const char *table_name, List_iterator<Item> *it,
              bool any_privileges, uint *hidden_bit_fields)
{
  Field_iterator_table_ref field_iterator;
  bool found;
  char name_buff[SAFE_NAME_LEN+1];
  DBUG_ENTER("insert_fields");
  DBUG_PRINT("arena", ("stmt arena: %p",thd->stmt_arena));

  if (db_name && lower_case_table_names)
  {


    strmake_buf(name_buff, db_name);
    my_casedn_str(files_charset_info, name_buff);
    db_name= name_buff;
  }

  found= FALSE;


  for (TABLE_LIST *tables= (table_name ? context->table_list :
                            context->first_name_resolution_table);
       tables;
       tables= (table_name ? tables->next_local :
                tables->next_name_resolution_table)
       )
  {
    Field *field;
    TABLE *table= tables->table;

    DBUG_ASSERT(tables->is_leaf_for_name_resolution());

    if ((table_name && my_strcasecmp(table_alias_charset, table_name,
                                     tables->alias.str)) ||
        (db_name && strcmp(tables->db.str, db_name)))
      continue;

#ifndef NO_EMBEDDED_ACCESS_CHECKS


    if (!any_privileges &&
        !tables->is_derived() &&
        !(tables->is_view() && (tables->grant.privilege & SELECT_ACL)) &&
        !(table && (table->grant.privilege & SELECT_ACL)))
    {
      field_iterator.set(tables);
      if (check_grant_all_columns(thd, SELECT_ACL, &field_iterator))
        DBUG_RETURN(TRUE);
    }
#endif


    if (table)
    {
      thd->lex->used_tables|= table->map;
      thd->lex->current_select->select_list_tables|= table->map;
    }


    field_iterator.set(tables);

    for (; !field_iterator.end_of_fields(); field_iterator.next())
    {


      if ((field= field_iterator.field()) && field->invisible != VISIBLE)
        continue;

      Item *item;

      if (!(item= field_iterator.create_item(thd)))
        DBUG_RETURN(TRUE);


      if (item->type() == Item::FIELD_ITEM && tables->cacheable_table)
        ((Item_field *)item)->cached_table= tables;

      if (!found)
      {
        found= TRUE;
        it->replace(item);
      }
      else
        it->after(item);

      if (item->type() == Item::FIELD_ITEM && item->field_type() == MYSQL_TYPE_BIT)
        (*hidden_bit_fields)++;

#ifndef NO_EMBEDDED_ACCESS_CHECKS


      if (any_privileges && !tables->is_with_table() && !tables->is_derived())
      {
        DBUG_ASSERT((tables->field_translation == NULL && table) ||
                    tables->is_natural_join);
        DBUG_ASSERT(item->type() == Item::FIELD_ITEM);
        Item_field *fld= (Item_field*) item;
        const char *field_table_name= field_iterator.get_table_name();

        if (!tables->schema_table &&
            !(fld->have_privileges=
              (get_column_grant(thd, field_iterator.grant(),
                                field_iterator.get_db_name(),
                                field_table_name, fld->field_name.str) &
               VIEW_ANY_ACL)))
        {
          my_error(ER_TABLEACCESS_DENIED_ERROR, MYF(0), "ANY",
                   thd->security_ctx->priv_user,
                   thd->security_ctx->host_or_ip,
                   field_table_name);
          DBUG_RETURN(TRUE);
        }
      }
#endif

      if ((field= field_iterator.field()))
      {
        field->table->mark_column_with_deps(field);
        if (table)
          table->covering_keys.intersect(field->part_of_key);
        if (tables->is_natural_join)
        {
          TABLE *field_table;


          Natural_join_column *nj_col;
          if (!(nj_col= field_iterator.get_natural_column_ref()))
            DBUG_RETURN(TRUE);
          DBUG_ASSERT(nj_col->table_field);
          field_table= nj_col->table_ref->table;
          if (field_table)
          {
            thd->lex->used_tables|= field_table->map;
            thd->lex->current_select->select_list_tables|=
              field_table->map;
            field_table->covering_keys.intersect(field->part_of_key);
            field_table->used_fields++;
          }
        }
      }
      else
        thd->lex->used_tables|= item->used_tables();
      thd->lex->current_select->cur_pos_in_select_list++;
    }


    if (table)
      table->used_fields= table->s->fields;
  }
  if (found)
    DBUG_RETURN(FALSE);


  if (!table_name)
    my_error(ER_NO_TABLES_USED, MYF(0));
  else if (!db_name && !thd->db.str)
    my_error(ER_NO_DB_ERROR, MYF(0));
  else
  {
    char name[FN_REFLEN];
    my_snprintf(name, sizeof(name), "%s.%s",
                db_name ? db_name : thd->get_db(), table_name);
    my_error(ER_BAD_TABLE_ERROR, MYF(0), name);
  }

  DBUG_RETURN(TRUE);
}
