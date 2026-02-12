longlong Item_null::val_int()
{

  DBUG_ASSERT(fixed == 1);
  null_value=1;
  return 0;
}
