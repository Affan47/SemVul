void Item_equal::merge(THD *thd, Item_equal *item)
{
  Item *c= item->get_const();
  if (c)
    item->equal_items.pop();
  equal_items.append(&item->equal_items);
  if (c)
  {


    add_const(thd, c);
  }
  cond_false|= item->cond_false;
}
