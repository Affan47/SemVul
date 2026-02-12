String *Item_sp_variable::val_str(String *sp)
{
  DBUG_ASSERT(fixed);
  Item *it= this_item();
  String *res= it->val_str(sp);

  null_value= it->null_value;

  if (!res)
    return NULL;


  if (res != &str_value)
    str_value.set(res->ptr(), res->length(), res->charset());
  else
    res->mark_as_const();

  return &str_value;
}
