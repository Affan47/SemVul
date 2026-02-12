String *Item_null::val_str(String *str)
{

  DBUG_ASSERT(fixed == 1);
  null_value=1;
  return 0;
}
