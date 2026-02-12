void Item_equal::update_const(THD *thd)
{
  List_iterator<Item> it(equal_items);
  if (with_const)
    it++;
  Item *item;
  while ((item= it++))
  {
    if (item->const_item() && !item->is_expensive() &&


        !item->is_outer_field())
    {
      if (item == equal_items.head())
        with_const= TRUE;
      else
      {
        it.remove();
        add_const(thd, item);
      }
    }
  }
}
