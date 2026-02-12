Item *Item_field::equal_fields_propagator(uchar *arg)
{
  if (no_const_subst)
    return this;
  item_equal= find_item_equal((COND_EQUAL *) arg);
  Item *item= 0;
  if (item_equal)
    item= item_equal->get_const();


  if (!item || !has_compatible_context(item))
    item= this;
  else if (field && (field->flags & ZEROFILL_FLAG) && IS_NUM(field->type()))
  {
    if (item && (cmp_context == STRING_RESULT || cmp_context == IMPOSSIBLE_RESULT))
      convert_zerofill_number_to_string(&item, (Field_num *)field);
    else
      item= this;
  }
  return item;
}
