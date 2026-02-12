void compute_part_of_sort_key_for_equals(JOIN *join, TABLE *table,
                                         Item_field *item_field,
                                         key_map *col_keys)
{
  col_keys->clear_all();
  col_keys->merge(item_field->field->part_of_sortkey);

  if (!optimizer_flag(join->thd, OPTIMIZER_SWITCH_ORDERBY_EQ_PROP))
    return;

  Item_equal *item_eq= NULL;

  if (item_field->item_equal)
  {


    item_eq= item_field->item_equal;
  }
  else
  {


    if (!join->cond_equal)
      return;
    table_map needed_tbl_map= item_field->used_tables() | table->map;
    List_iterator<Item_equal> li(join->cond_equal->current_level);
    Item_equal *cur_item_eq;
    while ((cur_item_eq= li++))
    {
      if ((cur_item_eq->used_tables() & needed_tbl_map) &&
          cur_item_eq->contains(item_field->field))
      {
        item_eq= cur_item_eq;
        item_field->item_equal= item_eq;
        break;
      }
    }
  }

  if (item_eq)
  {
    Item_equal_fields_iterator it(*item_eq);
    Item *item;

    while ((item= it++))
    {
      if (item->type() == Item::FIELD_ITEM &&
          ((Item_field*)item)->field->table == table)
      {
        col_keys->merge(((Item_field*)item)->field->part_of_sortkey);
      }
    }
  }
}
