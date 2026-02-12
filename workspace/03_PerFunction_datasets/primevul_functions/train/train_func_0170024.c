double Item_null::val_real()
{

  DBUG_ASSERT(fixed == 1);
  null_value=1;
  return 0.0;
}
