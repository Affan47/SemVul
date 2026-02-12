Item_func_isnull::remove_eq_conds(THD *thd, Item::cond_result *cond_value,
                                  bool top_level_arg)
{
  Item *real_item= args[0]->real_item();
  if (real_item->type() == Item::FIELD_ITEM)
  {
    Field *field= ((Item_field*) real_item)->field;

    if (((field->type() == MYSQL_TYPE_DATE) ||
         (field->type() == MYSQL_TYPE_DATETIME)) &&
         (field->flags & NOT_NULL_FLAG))
    {


      Item *item0= new(thd->mem_root) Item_int(thd, (longlong) 0, 1);
      Item *eq_cond= new(thd->mem_root) Item_func_eq(thd, args[0], item0);
      if (!eq_cond)
        return this;

      COND *cond= this;
      if (field->table->pos_in_table_list->is_inner_table_of_outer_join())
      {

        Item *or_cond= new(thd->mem_root) Item_cond_or(thd, eq_cond, this);
        if (!or_cond)
          return this;
        cond= or_cond;
      }
      else
      {

        cond= eq_cond;
      }

      cond->fix_fields(thd, &cond);


      return cond->Item::remove_eq_conds(thd, cond_value, false);
    }


    if (top_level_arg)
    {
      if (field->flags & AUTO_INCREMENT_FLAG && !field->table->maybe_null &&
          (thd->variables.option_bits & OPTION_AUTO_IS_NULL) &&
          (thd->first_successful_insert_id_in_prev_stmt > 0 &&
           thd->substitute_null_with_insert_id))
      {
  #ifdef HAVE_QUERY_CACHE
        query_cache_abort(thd, &thd->query_cache_tls);
  #endif
        COND *new_cond, *cond= this;

        if ((new_cond= new (thd->mem_root) Item_func_eq(thd, args[0],
                                        new (thd->mem_root) Item_int(thd, "last_insert_id()",
                                                     thd->read_first_successful_insert_id_in_prev_stmt(),
                                                     MY_INT64_NUM_DECIMAL_DIGITS))))
        {
          cond= new_cond;


          cond->fix_fields(thd, &cond);
        }


        thd->substitute_null_with_insert_id= FALSE;

        *cond_value= Item::COND_OK;
        return cond;
      }
    }
  }
  return Item::remove_eq_conds(thd, cond_value, top_level_arg);
}
