Item *Item_default_value::transform(Item_transformer transformer, uchar *args)
{
  DBUG_ASSERT(!current_thd->stmt_arena->is_stmt_prepare());


  if (!arg)
    return 0;

  Item *new_item= arg->transform(transformer, args);
  if (!new_item)
    return 0;


  if (arg != new_item)
    current_thd->change_item_tree(&arg, new_item);
  return (this->*transformer)(args);
}
