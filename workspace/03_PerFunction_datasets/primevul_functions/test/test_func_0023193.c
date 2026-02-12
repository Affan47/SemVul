void Item_cond::neg_arguments(THD *thd)
{
  List_iterator<Item> li(list);
  Item *item;
  while ((item= li++))
  {
    Item *new_item= item->neg_transformer(thd);
    if (!new_item)
    {
      if (!(new_item= new (thd->mem_root) Item_func_not(thd, item)))
	return;
    }
    (void) li.replace(new_item);
  }
}
