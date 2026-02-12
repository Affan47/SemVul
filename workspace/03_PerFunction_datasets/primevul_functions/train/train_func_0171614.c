find_order_in_list(THD *thd, Ref_ptr_array ref_pointer_array,
                   TABLE_LIST *tables,
                   ORDER *order, List<Item> &fields, List<Item> &all_fields,
                   bool is_group_field, bool add_to_all_fields,
                   bool from_window_spec)
{
  Item *order_item= *order->item;
  Item::Type order_item_type;
  Item **select_item;
  Field *from_field;
  uint counter;
  enum_resolution_type resolution;

  if (order_item->is_order_clause_position() && !from_window_spec)
  {
    uint count;
    if (order->counter_used)
      count= order->counter;
    else
      count= (uint) order_item->val_int();
    if (!count || count > fields.elements)
    {
      my_error(ER_BAD_FIELD_ERROR, MYF(0),
               order_item->full_name(), thd->where);
      return TRUE;
    }
    thd->change_item_tree((Item **)&order->item, (Item *)&ref_pointer_array[count - 1]);
    order->in_field_list= 1;
    order->counter= count;
    order->counter_used= 1;
    return FALSE;
  }

  select_item= find_item_in_list(order_item, fields, &counter,
                                 REPORT_EXCEPT_NOT_FOUND, &resolution);
  if (!select_item)
    return TRUE;


  if (select_item != not_found_item)
  {
    Item *view_ref= NULL;


    if (resolution == RESOLVED_BEHIND_ALIAS &&
        order_item->fix_fields_if_needed_for_order_by(thd, order->item))
      return TRUE;


    order_item_type= order_item->type();
    from_field= (Field*) not_found_field;
    if ((is_group_field && order_item_type == Item::FIELD_ITEM) ||
        order_item_type == Item::REF_ITEM)
    {
      from_field= find_field_in_tables(thd, (Item_ident*) order_item, tables,
                                       NULL, &view_ref, IGNORE_ERRORS, FALSE,
                                       FALSE);
      if (!from_field)
        from_field= (Field*) not_found_field;
    }

    if (from_field == not_found_field ||
        (from_field != view_ref_found ?

         ((*select_item)->type() == Item::FIELD_ITEM &&
          ((Item_field*) (*select_item))->field->eq(from_field)) :


         ((*select_item)->type() == Item::REF_ITEM &&
          view_ref->type() == Item::REF_ITEM &&
          ((Item_ref *) (*select_item))->ref ==
          ((Item_ref *) view_ref)->ref)))
    {


      order->item= &ref_pointer_array[counter];
      order->in_field_list=1;
      return FALSE;
    }
    else
    {


      push_warning_printf(thd, Sql_condition::WARN_LEVEL_WARN,
                          ER_NON_UNIQ_ERROR,
                          ER_THD(thd, ER_NON_UNIQ_ERROR),
                          ((Item_ident*) order_item)->field_name.str,
                          thd->where);
    }
  }
  else if (from_window_spec)
  {
    Item **found_item= find_item_in_list(order_item, all_fields, &counter,
                                         REPORT_EXCEPT_NOT_FOUND, &resolution,
                                         all_fields.elements - fields.elements);
    if (found_item != not_found_item)
    {
      order->item= &ref_pointer_array[all_fields.elements-1-counter];
      order->in_field_list= 0;
      return FALSE;
    }
  }

  order->in_field_list=0;


  if (order_item->fix_fields_if_needed_for_order_by(thd, order->item) ||
      thd->is_error())
    return TRUE;
  order_item= *order->item;

  if (!add_to_all_fields)
    return FALSE;

  uint el= all_fields.elements;

  all_fields.push_front(order_item, thd->mem_root);
  ref_pointer_array[el]= order_item;


  if (order_item->type() == Item::SUM_FUNC_ITEM)
    ((Item_sum *)order_item)->ref_by= all_fields.head_ref();

  order->item= &ref_pointer_array[el];
  return FALSE;
}
