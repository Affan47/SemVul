Item *Item_equal::transform(THD *thd, Item_transformer transformer, uchar *arg)
{
  DBUG_ASSERT(!thd->stmt_arena->is_stmt_prepare());

  Item *item;
  Item_equal_fields_iterator it(*this);
  while ((item= it++))
  {
    Item *new_item= item->transform(thd, transformer, arg);
    if (!new_item)
      return 0;


    if (new_item != item)
      thd->change_item_tree((Item **) it.ref(), new_item);
  }
  return Item_func::transform(thd, transformer, arg);
}
