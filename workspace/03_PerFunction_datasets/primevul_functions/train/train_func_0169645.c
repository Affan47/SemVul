bool Item_outer_ref::fix_fields(THD *thd, Item **reference)
{
  bool err;

  if ((*ref) && !(*ref)->fixed && ((*ref)->fix_fields(thd, reference)))
    return TRUE;
  err= Item_direct_ref::fix_fields(thd, reference);
  if (!outer_ref)
    outer_ref= *ref;
  if ((*ref)->type() == Item::FIELD_ITEM)
    table_name= ((Item_field*)outer_ref)->table_name;
  return err;
}
