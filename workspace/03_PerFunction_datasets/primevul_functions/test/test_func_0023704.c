Item *Item_cond::transform(THD *thd, Item_transformer transformer, uchar *arg)
{
  DBUG_ASSERT(!thd->stmt_arena->is_stmt_prepare());

  List_iterator<Item> li(list);
  Item *item;
  while ((item= li++))
  {
    Item *new_item= item->transform(thd, transformer, arg);
    if (!new_item)
      return 0;


    if (new_item != item)
      thd->change_item_tree(li.ref(), new_item);
  }
  return Item_func::transform(thd, transformer, arg);
}
