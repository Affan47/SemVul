bool Item_direct_view_ref::fix_fields(THD *thd, Item **reference)
{

  DBUG_ASSERT(*ref);

  if ((*ref)->fixed)
  {
    Item *ref_item= (*ref)->real_item();
    if (ref_item->type() == Item::FIELD_ITEM)
    {


      Field *fld= ((Item_field*) ref_item)->field;
      DBUG_ASSERT(fld && fld->table);
      if (thd->mark_used_columns == MARK_COLUMNS_READ)
        bitmap_set_bit(fld->table->read_set, fld->field_index);
    }
  }
  else if (!(*ref)->fixed &&
           ((*ref)->fix_fields(thd, ref)))
    return TRUE;

  if (Item_direct_ref::fix_fields(thd, reference))
    return TRUE;
  if (view->table && view->table->maybe_null)
    maybe_null= TRUE;
  set_null_ref_table();
  return FALSE;
}
