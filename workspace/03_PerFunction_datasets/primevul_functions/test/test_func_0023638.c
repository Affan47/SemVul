Item_cond::fix_fields(THD *thd, Item **ref)
{
  DBUG_ASSERT(fixed == 0);
  List_iterator<Item> li(list);
  Item *item;
  uchar buff[sizeof(char*)];
  bool is_and_cond= functype() == Item_func::COND_AND_FUNC;
  not_null_tables_cache= 0;
  used_tables_and_const_cache_init();


  and_tables_cache= ~(table_map) 0;

  if (check_stack_overrun(thd, STACK_MIN_SIZE, buff))
    return TRUE;


  while ((item=li++))
  {
    while (item->type() == Item::COND_ITEM &&
	   ((Item_cond*) item)->functype() == functype() &&
           !((Item_cond*) item)->list.is_empty())
    {
      li.replace(((Item_cond*) item)->list);
      ((Item_cond*) item)->list.empty();
      item= *li.ref();
    }
    if (abort_on_null)
      item->top_level_item();


    Item::Type type= item->type();
    if (type == Item::FIELD_ITEM || type == Item::REF_ITEM)
    {
      Query_arena backup, *arena;
      Item *new_item;
      arena= thd->activate_stmt_arena_if_needed(&backup);
      if ((new_item= new (thd->mem_root) Item_func_ne(thd, item, new (thd->mem_root) Item_int(thd, 0, 1))))
        li.replace(item= new_item);
      if (arena)
        thd->restore_active_arena(arena, &backup);
    }

    if (item->fix_fields_if_needed_for_bool(thd, li.ref()))
      return TRUE;
    item= *li.ref();
    used_tables_cache|=     item->used_tables();
    if (item->const_item() && !item->with_param &&
        !item->is_expensive() && !cond_has_datetime_is_null(item))
    {
      if (item->eval_const_cond() == is_and_cond && top_level())
      {


      }
      else
      {


        not_null_tables_cache= (table_map) 0;
        and_tables_cache= (table_map) 0;
      }
      if (thd->is_error())
        return TRUE;
    }
    else
    {
      table_map tmp_table_map= item->not_null_tables();
      not_null_tables_cache|= tmp_table_map;
      and_tables_cache&= tmp_table_map;

      const_item_cache= FALSE;
    }

    join_with_sum_func(item);
    with_param|=       item->with_param;
    with_field|=       item->with_field;
    m_with_subquery|=  item->with_subquery();
    with_window_func|= item->with_window_func;
    maybe_null|=       item->maybe_null;
  }
  if (fix_length_and_dec())
    return TRUE;
  fixed= 1;
  return FALSE;
}
