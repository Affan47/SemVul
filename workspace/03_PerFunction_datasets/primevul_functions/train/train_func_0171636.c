is_indexed_agg_distinct(JOIN *join, List<Item_field> *out_args)
{
  Item_sum **sum_item_ptr;
  bool result= false;

  if (join->table_count != 1 ||
      join->select_distinct ||
      join->select_lex->olap == ROLLUP_TYPE)
    return false;

  if (join->make_sum_func_list(join->all_fields, join->fields_list, true))
    return false;

  Bitmap<MAX_FIELDS> first_aggdistinct_fields;
  bool first_aggdistinct_fields_initialized= false;
  for (sum_item_ptr= join->sum_funcs; *sum_item_ptr; sum_item_ptr++)
  {
    Item_sum *sum_item= *sum_item_ptr;
    Item *expr;

    switch (sum_item->sum_func())
    {
      case Item_sum::MIN_FUNC:
      case Item_sum::MAX_FUNC:
        continue;
      case Item_sum::COUNT_DISTINCT_FUNC:
        break;
      case Item_sum::AVG_DISTINCT_FUNC:
      case Item_sum::SUM_DISTINCT_FUNC:
        if (sum_item->get_arg_count() == 1)
          break;

      default: return false;
    }


    Bitmap<MAX_FIELDS> cur_aggdistinct_fields;
    cur_aggdistinct_fields.clear_all();
    for (uint i= 0; i < sum_item->get_arg_count(); i++)
    {
      expr= sum_item->get_arg(i);

      if (expr->real_item()->type() != Item::FIELD_ITEM)
        return false;

      Item_field* item= static_cast<Item_field*>(expr->real_item());
      if (out_args)
        out_args->push_back(item, join->thd->mem_root);

      cur_aggdistinct_fields.set_bit(item->field->field_index);
      result= true;
    }


    if (!first_aggdistinct_fields_initialized)
    {
      first_aggdistinct_fields= cur_aggdistinct_fields;
      first_aggdistinct_fields_initialized=true;
    }
    else if (first_aggdistinct_fields != cur_aggdistinct_fields)
      return false;
  }

  return result;
}
