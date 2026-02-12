String *Item_uint::val_str(String *str)
{

  DBUG_ASSERT(fixed == 1);
  str->set((ulonglong) value, collation.collation);
  return str;
}
