void Item_equal::add_const(THD *thd, Item *c)
{
  if (cond_false)
    return;
  if (!with_const)
  {
    with_const= TRUE;
    equal_items.push_front(c, thd->mem_root);
    return;
  }


  cond_false= !Item_equal::compare_type_handler()->Item_eq_value(thd, this, c,
                                                                 get_const());
  if (with_const && equal_items.elements == 1)
    cond_true= TRUE;
  if (cond_false || cond_true)
    const_item_cache= 1;
}
