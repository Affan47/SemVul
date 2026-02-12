bool setup_fields(THD *thd, Ref_ptr_array ref_pointer_array,
                  List<Item> &fields, enum_column_usage column_usage,
                  List<Item> *sum_func_list, List<Item> *pre_fix,
                  bool allow_sum_func)
{
  Item *item;
  enum_column_usage saved_column_usage= thd->column_usage;
  nesting_map save_allow_sum_func= thd->lex->allow_sum_func;
  List_iterator<Item> it(fields);
  bool save_is_item_list_lookup;
  bool make_pre_fix= (pre_fix && (pre_fix->elements == 0));
  DBUG_ENTER("setup_fields");
  DBUG_PRINT("enter", ("ref_pointer_array: %p", ref_pointer_array.array()));

  thd->column_usage= column_usage;
  DBUG_PRINT("info", ("thd->column_usage: %d", thd->column_usage));


  DBUG_ASSERT(thd->lex->current_select->nest_level >= 0);
  DBUG_ASSERT(thd->lex->current_select->master_unit()->first_select()
                ->nest_level ==
              thd->lex->current_select->nest_level);
  if (allow_sum_func)
    thd->lex->allow_sum_func.set_bit(thd->lex->current_select->nest_level);
  thd->where= THD::DEFAULT_WHERE;
  save_is_item_list_lookup= thd->lex->current_select->is_item_list_lookup;
  thd->lex->current_select->is_item_list_lookup= 0;


  if (!ref_pointer_array.is_null())
  {
    DBUG_ASSERT(ref_pointer_array.size() >= fields.elements);
    memset(ref_pointer_array.array(), 0, sizeof(Item *) * fields.elements);
  }


  List_iterator<Item_func_set_user_var> li(thd->lex->set_var_list);
  Item_func_set_user_var *var;
  while ((var= li++))
    var->set_entry(thd, FALSE);

  Ref_ptr_array ref= ref_pointer_array;
  thd->lex->current_select->cur_pos_in_select_list= 0;
  while ((item= it++))
  {
    if (make_pre_fix)
      pre_fix->push_back(item, thd->stmt_arena->mem_root);

    if (item->fix_fields_if_needed_for_scalar(thd, it.ref()))
    {
      thd->lex->current_select->is_item_list_lookup= save_is_item_list_lookup;
      thd->lex->allow_sum_func= save_allow_sum_func;
      thd->column_usage= saved_column_usage;
      DBUG_PRINT("info", ("thd->column_usage: %d", thd->column_usage));
      DBUG_RETURN(TRUE);
    }
    item= *(it.ref());
    if (!ref.is_null())
    {
      ref[0]= item;
      ref.pop_front();
    }


    if (sum_func_list &&
         ((item->with_sum_func() && item->type() != Item::SUM_FUNC_ITEM) ||
          item->with_window_func))
    {
      item->split_sum_func(thd, ref_pointer_array, *sum_func_list,
                           SPLIT_SUM_SELECT);
    }
    thd->lex->current_select->select_list_tables|= item->used_tables();
    thd->lex->used_tables|= item->used_tables();
    thd->lex->current_select->cur_pos_in_select_list++;
  }
  thd->lex->current_select->is_item_list_lookup= save_is_item_list_lookup;
  thd->lex->current_select->cur_pos_in_select_list= UNDEF_POS;

  thd->lex->allow_sum_func= save_allow_sum_func;
  thd->column_usage= saved_column_usage;
  DBUG_PRINT("info", ("thd->column_usage: %d", thd->column_usage));
  DBUG_RETURN(MY_TEST(thd->is_error()));
}
