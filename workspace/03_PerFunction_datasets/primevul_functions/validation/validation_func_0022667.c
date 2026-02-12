update_ref_and_keys(THD *thd, DYNAMIC_ARRAY *keyuse,JOIN_TAB *join_tab,
                    uint tables, COND *cond, table_map normal_tables,
                    SELECT_LEX *select_lex, SARGABLE_PARAM **sargables)
{
  uint	and_level,i;
  KEY_FIELD *key_fields, *end, *field;
  uint sz;
  uint m= MY_MAX(select_lex->max_equal_elems,1);
  DBUG_ENTER("update_ref_and_keys");
  DBUG_PRINT("enter", ("normal_tables: %llx", normal_tables));

  SELECT_LEX *sel=thd->lex->current_select;
  sel->cond_count= 0;
  sel->between_count= 0;
  if (cond)
    cond->walk(&Item::count_sargable_conds, 0, sel);
  for (i=0 ; i < tables ; i++)
  {
    if (*join_tab[i].on_expr_ref)
      (*join_tab[i].on_expr_ref)->walk(&Item::count_sargable_conds, 0, sel);
  }
  {
    List_iterator<TABLE_LIST> li(*join_tab->join->join_list);
    TABLE_LIST *table;
    while ((table= li++))
    {
      if (table->nested_join)
        count_cond_for_nj(sel, table);
    }
  }


  sz= MY_MAX(sizeof(KEY_FIELD),sizeof(SARGABLE_PARAM))*
    ((sel->cond_count*2 + sel->between_count)*m+1);
  if (!(key_fields=(KEY_FIELD*)	thd->alloc(sz)))
    DBUG_RETURN(TRUE);
  and_level= 0;
  field= end= key_fields;
  *sargables= (SARGABLE_PARAM *) key_fields +
                (sz - sizeof((*sargables)[0].field))/sizeof(SARGABLE_PARAM);

  (*sargables)[0].field= 0;

  if (my_init_dynamic_array2(keyuse, sizeof(KEYUSE),
                             thd->alloc(sizeof(KEYUSE) * 20), 20, 64,
                             MYF(MY_THREAD_SPECIFIC)))
    DBUG_RETURN(TRUE);

  if (cond)
  {
    KEY_FIELD *saved_field= field;
    cond->add_key_fields(join_tab->join, &end, &and_level, normal_tables,
                         sargables);
    for (; field != end ; field++)
    {


      if (field->val->type() == Item::NULL_ITEM &&
	  !field->field->real_maybe_null())
	field->field->table->reginfo.not_exists_optimize=1;
    }
    field= saved_field;
  }
  for (i=0 ; i < tables ; i++)
  {


    if (*join_tab[i].on_expr_ref)
      (*join_tab[i].on_expr_ref)->add_key_fields(join_tab->join, &end,
                                                 &and_level,
                                                 join_tab[i].table->map,
                                                 sargables);
  }


  {
    List_iterator<TABLE_LIST> li(*join_tab->join->join_list);
    TABLE_LIST *table;
    while ((table= li++))
    {
      if (table->nested_join)
        add_key_fields_for_nj(join_tab->join, table, &end, &and_level,
                              sargables);
    }
  }


  for ( ; field != end ; field++)
  {
    if (add_key_part(keyuse,field))
      DBUG_RETURN(TRUE);
  }

  if (select_lex->ftfunc_list->elements)
  {
    if (add_ft_keys(keyuse,join_tab,cond,normal_tables))
      DBUG_RETURN(TRUE);
  }

  DBUG_RETURN(FALSE);
}
